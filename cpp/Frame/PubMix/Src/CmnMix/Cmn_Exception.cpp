#include "stdafx.h"
#include <CmnMix/Cmn_Exception.h>
#include <protect/Protect.h>
#include <cassert>
#include <CmnMix/Cmn_LuaOper.h>
#include <CommonX/CmnX_DllApi.h>
#include <CmnMix/Cmn_LuaOper.h>
#include <CmnMix/Cmn_LogOut.h>

CmnExceptionBase::CmnExceptionBase(const std::string& msg) : std::runtime_error(msg)
{
}

CmnExceptionBase::CmnExceptionBase() : std::runtime_error("")
{
}

CmnExceptionBase::CmnExceptionBase(const char* msg) : std::runtime_error(msg)
{
}

CmnExceptionBase::CmnExceptionBase(const CmnExceptionBase& rhs) : std::runtime_error(rhs)
{
}

CmnExceptionBase::~CmnExceptionBase()
{

}

const CmnExceptionBase* CmnExceptionBase::GetDelayException()
{
	return delay_exception_.get();
}

void CmnExceptionBase::SetDelayException(const CmnExceptionBase& cur_exception)
{
	assert(delay_exception_.get() != &cur_exception);
	delay_exception_.reset(cur_exception.Clone());
}

void CmnExceptionBase::SetDelayException(const CmnExceptionBase* cur_exception)
{
	delay_exception_.reset((CmnExceptionBase*)cur_exception);
}

void CmnExceptionBase::CatchDelayException()
{
	try{
		throw;
	}
	DO_CATCH_THE_EXCEPTION(const CmnExceptionBase& e, {
		SetDelayException(e);
		assert(GetDelayException());
	})
}

void CmnExceptionBase::HandleDelayException()
{
	auto delay_except = delay_exception_.get();
	if (!delay_except)
	{
		using namespace luabind;
		lua_State* lua_state = nullptr;
		try{
			throw;
		} DO_CATCH_THE_EXCEPTION(const luabind::error& e, {
			lua_state = e.state();
		}) DO_CATCH_THE_EXCEPTION(const luabind::cast_failed& e, {
			lua_state = e.state();
		})
		if (lua_state)
		{
			object err_msg(from_stack(lua_state, -1));
			lua_pop(lua_state, 1);
			throw CmnLuaException(LuaObjCast(err_msg, "û�д�����Ϣ�Ľű�����1"));
		}
		assert(!"����ִ�е��˴�");
		return;
	}
	try{
		delay_except->Rethrow();
	} DO_CATCH_THE_EXCEPTION(const CmnExceptionBase&, {
		CmnExceptionBase::SetDelayException(nullptr);
		throw;
	})
}

luabind::object CmnExceptionBase::SafeRun_SkipExcept(const luabind::object& lua_func, const luabind::object& deault_res)
{
	try{
		assert(LUA_TFUNCTION == luabind::type(lua_func));
		return LuaObjCallByDlt(lua_func, deault_res);
	}
	DO_CATCH_THE_EXCEPTION( const CmnSafeRun_SkipExcept& e, {
		std::string err_str(e.what());
		if ( !err_str.empty() )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << err_str;
		}
	})
	return deault_res;
}

bool CmnExceptionBase::IsIgnoreException_(const char* expression_str, const char* func_name, const char* file_name, unsigned int file_line, const char* another_prompt)
{
	assert(expression_str);
	assert(func_name);
	assert(file_name);	
	std::string str_msg = "���ʽ��";
	str_msg += expression_str;
	str_msg += "\n������";
	str_msg += func_name;
	str_msg += "\n�ļ���";
	str_msg += file_name;
	str_msg += "\n�кţ�";
	str_msg += std::to_string(file_line);
	if (another_prompt)
	{
		str_msg += "\n������";
		str_msg += another_prompt;
	}
	str_msg += "\n�Ƿ���Ҫ��ס��";
	return IDOK != MessageBoxTimeout(nullptr, str_msg.c_str(), "����", MB_OKCANCEL, 0, 1000 * 30);
}

std::string CmnExceptionBase::DefCatchCall(const std::function<std::string()>& func)
{
	using namespace luabind;
	try{
		return func();
	} DO_CATCH_THE_EXCEPTION(const CmnTerminateScriptException& e, {
		return e.what();
	}) DO_CATCH_THE_EXCEPTION(const CmnSafeRun_SkipExcept& e, {
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "��ȫִ��֮�����쳣->" << e.what();
		assert(false);
		return "��ȫִ��֮�����쳣";
	}) DO_CATCH_THE_EXCEPTION(const CmnPauseLogicException& e, {
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "�ж��߼��쳣, id->" << e.id_.id_ << " ԭ��->" << e.what();
		assert(false);
		return "�ж��߼��쳣";
	}) DO_CATCH_THE_EXCEPTION(const CmnGeneralRunException& e, {
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "��ͨ���д���->" << e.what();
		assert(false);
		return "��ͨ���д���";
	}) DO_CATCH_THE_EXCEPTION(const CmnLuaException& e, {
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "lua�ű�����->" << e.what();
		//assert(false);
		return "lua�ű�����";
	}) DO_CATCH_THE_EXCEPTION(const luabind::error& e, {
		object err_msg(from_stack(e.state(), -1));		
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ű�����->" << LuaObjCast(err_msg, "û�д�����Ϣ�Ľű�����3");
		assert(false);
		return "�ű�����";
	}) DO_CATCH_THE_EXCEPTION(const luabind::cast_failed& e, {
		object err_msg(from_stack(e.state(), -1));
		LOG_ENTER_FUNC;
		LOG_O(Log_debug) << "�������д���->" << LuaObjCast(err_msg, "û�д�����Ϣ��cast failed����") << " ->" << e.info().name();
		assert(false);
		return "�������д���";
	}) DO_CATCH_THE_EXCEPTION(const CmnExceptionBase&, {
			throw;
	}) DO_CATCH_ALL_EXCEPTION({
			LOG_ENTER_FUNC;
			LOG_O(Log_debug) << "����δ֪�����ش���";
			assert(false);
			throw;
	})
	assert(false);
	return std::string("������ִ�е����ﰡ");
}

boost::thread_specific_ptr<CmnExceptionBase> CmnExceptionBase::delay_exception_;

CmnTerminateScriptException::CmnTerminateScriptException() : CmnExceptionBase(" ��ֹͣ")
{
}

CmnTerminateScriptException::CmnTerminateScriptException(const char* msg) : CmnExceptionBase(msg)
{
}

CmnTerminateScriptException::CmnTerminateScriptException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnGeneralRunException::CmnGeneralRunException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnGeneralRunException::CmnGeneralRunException(const char* msg) : CmnExceptionBase(msg)
{
}

CmnTerminateProcessException::CmnTerminateProcessException()
{
}

CmnTerminateProcessException::CmnTerminateProcessException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnTerminateProcessException::CmnTerminateProcessException(const char* msg) : CmnExceptionBase(msg)
{
}

CmnExitIoThreadException::CmnExitIoThreadException()
{
}

CmnExitIoThreadException::CmnExitIoThreadException(const char* msg) : CmnExceptionBase(msg)
{
}

CmnExitIoThreadException::CmnExitIoThreadException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnReDoIoRunException::CmnReDoIoRunException()
{
}

CmnReDoIoRunException::CmnReDoIoRunException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnReDoIoRunException::CmnReDoIoRunException(const char* msg) : CmnExceptionBase(msg)
{
}

CmnLetIoThreadDoErr::CmnLetIoThreadDoErr()
{
}

CmnLetIoThreadDoErr::CmnLetIoThreadDoErr(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnLetIoThreadDoErr::CmnLetIoThreadDoErr(const char* msg) : CmnExceptionBase(msg)
{
}

CmnCloseProcessException::CmnCloseProcessException()
{
}

CmnCloseProcessException::CmnCloseProcessException(const std::string& msg) : CmnExceptionBase(msg)
{
}

CmnCloseProcessException::CmnCloseProcessException(const char* msg) : CmnExceptionBase(msg)
{
}

std::string GenCastFailedStr_(const luabind::type_id& src, const char* middle_str_info, const luabind::type_id& to){
	std::string res = src.name();
	if (middle_str_info)
	{
		res += ' ';
		res += middle_str_info;
	}
	res += " cast failed to->";
	res += to.name();
	return std::move(res);
}
CmnCastException::CmnCastException(const luabind::type_id& src, const luabind::type_id& to) : CmnExceptionBase(GenCastFailedStr_(src, nullptr, to))
{
}

CmnCastException::CmnCastException(const luabind::type_id& src, const std::string& middle_str_info, const luabind::type_id& to) : CmnExceptionBase(GenCastFailedStr_(src, middle_str_info.c_str(), to))
{
}

CmnCastException::CmnCastException(const luabind::type_id& src, const char* middle_str_info, const luabind::type_id& to) : CmnExceptionBase(GenCastFailedStr_(src, middle_str_info, to))
{
}

CmnLuaException::CmnLuaException(const std::string& msg) : CmnExceptionBase(msg)
{

}

CmnSafeRun_SkipExcept::CmnSafeRun_SkipExcept(const std::string& msg) : CmnExceptionBase(msg)
{

}

CmnSafeRun_SkipExcept::CmnSafeRun_SkipExcept(const char* msg) : CmnExceptionBase(msg)
{

}

CmnSafeRun_SkipExcept::CmnSafeRun_SkipExcept() : CmnExceptionBase()
{
}

CmnPauseLogicException::CmnPauseLogicException(PauseIdentity id, const char* msg) : CmnExceptionBase(msg), id_(id)
{
}

CmnPauseLogicException::CmnPauseLogicException(PauseIdentity id) : id_(id)
{
}

bool CmnPauseLogicException::IsIdentityEqual(PauseIdentity id) const
{
	return id_.id_ == id.id_;
}
