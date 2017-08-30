#include "stdafx.h"
#include "GClass.h"
#include <cassert>
#include "Common/LogOut.h"
#include "FuncObjC.h"
#include "GAddr.h"
#include "Protocol/P_BaseStruct.h"
#include "GOffset.h"
#include "GFuncCall.h"
#include "FuncObjC.h"
#include "Common/JsonMore.h"
#include "Net/PocoMore.h"
#include "json/writer.h"
#include <openssl/ssl.h>
#include <Communicate/CGL_Defines.h>

using namespace GClass;
using namespace GAddr;
using namespace GType;
using namespace GOffset;
using namespace GFuncCall;

class HttpPackageParser : public FindBetweenStringA{
public:
	HttpPackageParser( const char* str_begin,  const char* str_end ) : FindBetweenStringA(str_begin, str_end){
		str_c_result_ = "";
	}

	void ParsePackage( const char* http_package ){
		const auto& range_ptr = Parse(http_package);
		if ( range_ptr.first == range_ptr.second )
			return;
		str_result_.assign(range_ptr.first, range_ptr.second);
		str_c_result_ = str_result_.c_str();
	}

	void ParseHost( const char* http_package ){
		const auto& range_ptr = Parse(http_package);
		if ( range_ptr.first == range_ptr.second )
			return;
		if ( atoi(range_ptr.first + 5) == 0 )
			return;
		str_result_.assign(range_ptr.first, range_ptr.second);
		str_c_result_ = str_result_.c_str();
	}

	const char*				str_c_result_;
private:
	std::string				str_result_;
};

HandleSendPackage& GClass::HandleSendPackage::GetMe()
{
	static HandleSendPackage handler;
	return handler;
}

const char* GClass::HandleSendPackage::EncodeContentLength( const char* msg )
{
	if ( !msg )
		return "";

	static char buffer[70];
	sprintf_s(buffer, "Content-Length: %d\r\n\r\n", strlen(msg));
	return buffer;
}

const char* GClass::HandleSendPackage::EncodeContentLength( std::size_t msg_size )
{
	if ( 0 == msg_size )
		return "";

	static char buffer[70];
	sprintf_s(buffer, "Content-Length: %d\r\n\r\n", msg_size);
	return buffer;
}

std::string GClass::HandleSendPackage::HttpPackage_CombineNormalMsgHead(
	const char* msg_catalog, const char* msg )
{
	return std::move(std::move(HttpPackage_CombineNormalMsgHead_(msg_catalog)) + EncodeContentLength(msg));
}

std::string GClass::HandleSendPackage::HttpPackage_CombineNormalMsgHead(
	const char* msg_catalog, const std::string& msg )
{
	return std::move(std::move(HttpPackage_CombineNormalMsgHead_(msg_catalog)) + EncodeContentLength(msg.size()));
}
GClass::HandleSendPackage::HandleSendPackage()
{

}

void GClass::HandleSendPackage::HandleSendPakcageOfGame( const std::string& package_send )
{
	//LOG_ENTER_FUNC;
	auto package_begin = package_send.c_str();
	//����
	HandleHttpPackage::UpdateHandler(package_begin);

	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_O(Log_warning) << "func obj normal��δ����";
		return;
	}

	HTTPRequest_RFB request;
	if ( !request.ReadFromBuffer(package_send) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "ReadFromBuffer����";
		return;
	}

	auto handle_http = GClass::HandleHttpPackage::GetInstance();
	if (handle_http)
	{
		handle_http->SetHost(request.getHost());
		Poco::Net::NameValueCollection cookie_tmp;
		request.getCookies(cookie_tmp);
		if ( !cookie_tmp.empty() )
		{
			handle_http->SetCookie(cookie_tmp);
		}
	}
	if (HandleHttpPackage::ContentTypeIsJson(package_begin))
	{
		auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(package_begin);
		if ( !first_msg_char_addr )
		{
			LOG_O(Log_fatal) << "������json��ʽ���ĵ���Ϊɶû���ҵ���Ϣ���ݣ�";
			return;
		}
#ifdef D_SOME_LOG
		LOG_O(Log_trace).operator << ("��Ϸ��������Ϣͷ�ǣ�")
			.write(package_begin, std::distance(package_begin, first_msg_char_addr));
#endif

		const auto& msg = Utf8ToGbk(first_msg_char_addr);

		//LOG_O(Log_trace) << "��Ϸ��������Ϣ�ǣ�" << msg;

		Json::Value root;
		if ( JsonReader::GetMe().ParseCStr(msg.c_str(), root) )
		{
			func_obj_normal->GetGLua().LuaObjCall<void>("HandleSendHttpPackage", &request, &root);
		}
		else
		{
			func_obj_normal->GetGLua().LuaObjCall<void>("HandleSendHttpPackage", &request);
		}
	}
	/*else if (HandleHttpPackage::ContentTypeIsXgzip(package_begin))
	{
		auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(package_begin);
		if ( !first_msg_char_addr )
		{
			LOG_O(Log_fatal) << "������x-gzip��ʽ���ĵ���Ϊɶû���ҵ���Ϣ���ݣ�";
			return;
		}
		HTTPRequest_RFB http_request;
		if ( !http_request.ReadFromBuffer(package_send) )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_warning) << "ReadFromBuffer����";
			return;
		}
		//ԭʼ����
		std::string str_original;
		VERIFY(http_request.DeContentAsGzip(str_original));
		const char* cstr_original = str_original.c_str();
		cstr_original += 0;

		LOG_O(Log_trace) << "gzip,Method->" << http_request.getMethod() << "\turi->" << http_request.getURI()
			<< "\tMsg->" << str_original;
	}*/
	else
	{
#ifdef D_SOME_LOG
		LOG_O(Log_trace) << "��Ϸ�����ˣ�����uri��" << request.getURI();
		//LOG_O(Log_trace) << "��Ϸ�����ˣ��������������ǣ�" << package_send;
#endif
		func_obj_normal->GetGLua().LuaObjCall<void>("HandleSendHttpPackage", &request);
	}
}

std::string GClass::HandleSendPackage::HttpPackage_CombineNormalMsgHead_( const char* msg_catalog )
{
	auto handle_package = HandleHttpPackage::GetInstance();
	if ( !handle_package )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "HandleHttpPackageʵ����δ����";
		return "";
	}
	std::string package_head = handle_package->Post();
	package_head += msg_catalog;
	package_head += handle_package->HttpVersion();
	package_head += handle_package->Host();
	package_head += handle_package->Accept();
	package_head += handle_package->Cookie();
	package_head += handle_package->Connection();
	package_head += handle_package->ContentType();
	return std::move(package_head);
}

std::string GClass::HandleSendPackage::HttpPackage_CombineGzipMsgHead( const char* msg_catalog, const std::string& msg )
{
	auto handle_package = HandleHttpPackage::GetInstance();
	if ( !handle_package )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "HandleHttpPackageʵ����δ����";
		return "";
	}
	std::string package_head = handle_package->Post();
	package_head += msg_catalog;
	package_head += handle_package->HttpVersion();
	package_head += handle_package->Host();
	package_head += handle_package->Accept();
	package_head += handle_package->Cookie();
	package_head += handle_package->Connection();
	package_head += handle_package->ContentGzipType();
	package_head += EncodeContentLength(msg.size());
	return std::move(package_head);
}

std::string GClass::HandleSendPackage::HttpPackage_CombinePostMsgHead( const char* uri )
{
	auto handle_package = HandleHttpPackage::GetInstance();
	if ( !handle_package )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "HandleHttpPackageʵ����δ����";
		return "";
	}
	std::string package_head = handle_package->Get();
	package_head += uri;
	package_head += handle_package->HttpVersion();
	package_head += handle_package->Host();
	package_head += handle_package->Accept();
	package_head += handle_package->Cookie();
	package_head += handle_package->Connection();
	package_head += "\r\n";
	return std::move(package_head);
}

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackage( const char* msg_head, const char* msg, std::size_t msg_size, bool is_async )
{
	/*LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "param msg_head:" << msg_head << "��param msg:" << msg;*/
	assert(false);
	return enHttpSendCall_Result_Fail;
	if ( !msg_head || !msg )
		return enHttpSendCall_Result_Fail;
	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return enHttpSendCall_Result_Fail;
	//////////////////////////////////////////////////////////////////////////
	//ͨ��ssl_write����
	enHttpSendCall_Result res = enHttpSendCall_Result_Succeed;
	auto http_content = std::make_shared<std::string>();
	if ( !http_content )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_fatal) << "new http contentʧ��";
		return enHttpSendCall_Result_Fail;
	}
	*http_content = msg_head;
	http_content->append(msg, msg_size);
	if (is_async)
	{
		gwnd->AsyncExec([=](){
			DoSend_Impl(http_content->c_str(), http_content->size());
		});
	}
	else
	{
		gwnd->SyncExec(res, [=](){
			return DoSend_Impl(http_content->c_str(), http_content->size());
		});
	}
	return res;
	//////////////////////////////////////////////////////////////////////////
	/*GType::stHttpSendCall_NeededObj3* obj3 = nullptr;
	if ( !MemOperApplyR(obj3, GAddr::g_pGameBase, GOffset::g_o_HttpSendCall_NeededObj3) || nullptr == obj3 )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "stHttpSendCall_NeededObj3Ϊ�գ����ڻ����ܷ���";
		return enHttpSendCall_Result_Fail;
	}

	HttpSendCall_NeededObj2* obj2 = nullptr;
	if ( !MemOperApplyR(obj2, g_pGameBase, g_o_HttpSendCall_NeededObj2) || nullptr == obj2 )
		return enHttpSendCall_Result_Fail;
	HttpSendCall_NeededObj1* obj1 = nullptr;
	if ( !MemOperGetAddr(obj1, g_pGameBase, g_o_HttpSendCall_NeededObj1) || nullptr == obj1 )
		return enHttpSendCall_Result_Fail;

	stHttpSendCall_Content* http_content = (stHttpSendCall_Content*)CallocOfGame(1, sizeof(stHttpSendCall_Content));
	if ( !http_content )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "CallocOfGame�����ڴ�ʧ��";
		return enHttpSendCall_Result_Fail;
	}
	//��Ч��Ϣ�ĳ���
	const int kMsgSize = msg_size;
	const int kMsgHeadSize = strlen(msg_head);
	http_content->total_size_http_content = kMsgSize + kMsgHeadSize;
	http_content->unknown_equal_zero = 0;

	char* str_buffer = (char*)MallocOfGame(http_content->total_size_http_content + 1 + sizeof(stSpecifyTag_T<DWORD>));
	if ( !str_buffer )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "MallocOfGame�����ڴ�ʧ��";
		return enHttpSendCall_Result_Fail;
	}
	http_content->str_http_content = str_buffer;

	CopyMemory(str_buffer, msg_head, kMsgHeadSize);
	str_buffer += kMsgHeadSize;
	CopyMemory(str_buffer, msg, kMsgSize);
	str_buffer += kMsgSize;
	*str_buffer = '\0';
	new (++str_buffer) stSpecifyTag_T<DWORD>("&*_+");
	str_buffer = nullptr;

	enHttpSendCall_Result res = enHttpSendCall_Result_Succeed;
	auto fn = [=](){
		return SendHttpPackage_Impl(http_content, obj2, obj1, kMsgSize);
	};

	if (is_async)
	{
		gwnd->AsyncExec(fn);
	}
	else
	{
		gwnd->SyncExec(res, fn);
	}
	return res;*/
}

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackage( const char* msg_head, const std::string& msg, bool is_async )
{
	return SendHttpPackage(msg_head, msg.c_str(), msg.size(), is_async);
}

HttpPackageSend& GClass::HttpPackageSend::GetMe()
{
	static HttpPackageSend send_handle;
	return send_handle;
}

/*
GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackageAsync( const char* msg_head, const char* msg )
{
	auto res = GetMe().SendHttpPackage(msg_head, msg, true);
	if ( enHttpSendCall_Result_Fail == res )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "����û�гɹ�";
	}
	return res;
}*/

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackageAsync( const char* msg_head, const std::string& msg )
{
	assert(false);
	return GType::enHttpSendCall_Result_Fail;
	auto res = GetMe().SendHttpPackage(msg_head, msg, true);
	if ( enHttpSendCall_Result_Fail == res )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "����û�гɹ�";
	}
	return res;
}

/*
GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackageSync( const char* msg_head, const char* msg )
{
	auto res = GetMe().SendHttpPackage(msg_head, msg, false);
	if ( enHttpSendCall_Result_Fail == res )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "����û�гɹ�";
	}
	return res;
}
*/

GClass::HttpPackageSend::HttpPackageSend() : rectify_send_count_(0, 0)
{
	game_sending_ = 0;
	reset_sending_cnt_ = false;
}

/*
GType::enHttpSendCall_Result GClass::HttpPackageSend::SendNormalMsgAsync( const char* uri, const char* msg )
{
	if ( !msg )
		msg = "";

	const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombineNormalMsgHead(uri, msg);
	return SendHttpPackageAsync(msg_head.c_str(), msg);
}*/

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendNormalMsgAsync( const char* uri, const std::string& msg )
{
	static std::string kJsonEmpty("{}");
	const auto& real_msg = msg.empty() ? kJsonEmpty : msg;
	const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombineNormalMsgHead(uri, real_msg);
	return SendHttpPackageAsync(msg_head.c_str(), real_msg);
}

/*
GType::enHttpSendCall_Result GClass::HttpPackageSend::SendNormalMsgSync( const char* uri, const char* msg )
{
	const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombineNormalMsgHead(uri, msg);
	return SendHttpPackageSync(msg_head.c_str(), msg);
}*/

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendJsonMsgAsync( const char* uri, const Json::Value& msg )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return GType::enHttpSendCall_Result_Fail;
	}
	Json::FastWriter json_writer;
	const auto& str_msg = json_writer.write(msg);
	return SendNormalMsgAsync(uri, str_msg.c_str());
}

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendEncryptedJsonMsgAsync( const char* uri, const Json::Value& msg )
{
	assert(uri);
	if (uri)
	{
		HTTPRequest_RFB encode_json;
		encode_json.EnJsonContentAsGzip(msg);

		const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombineGzipMsgHead(uri, encode_json.GetRealMsg());
		return SendHttpPackageAsync(msg_head.c_str(), encode_json.GetRealMsg());
	}
	return GType::enHttpSendCall_Result_Fail;
}

GType::enHttpSendCall_Result GClass::HttpPackageSend::SendHttpPackage_Impl(  GType::stHttpSendCall_Content* http_content, GType::HttpSendCall_NeededObj2* obj2, 
			GType::HttpSendCall_NeededObj1* obj1, int msg_size )
{
	assert(false);
	return enHttpSendCall_Result_Fail;
	/*LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��Ϸ���̵߳�����Ϸ�е�send http call";*/
	/*GType::stHttpSendCall_NeededObj3* obj3 = nullptr;
	if ( !http_content || !http_content->str_http_content ||
		!MemOperApplyR(obj3, GAddr::g_pGameBase, GOffset::g_o_HttpSendCall_NeededObj3) || nullptr == obj3 )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "stHttpSendCall_NeededObj3Ϊ�գ����ܷ���";

		//�ͷ��ڴ�
		GFuncCall::FreeOfGame((char*)http_content->str_http_content);
		GFuncCall::FreeOfGame(http_content);
		return enHttpSendCall_Result_Fail;
	}

	//�Լ��������Լ��հ�
	auto package_handler = HandleHttpPackage::GetInstance();
	//package_handler = nullptr;
	if ( package_handler && FuncObj_NormalC::GetInstance() )
	{
		auto http_method = package_handler->GetMethodFromHttpPackage(http_content->str_http_content);
		if ( http_method.first != http_method.second )
		{
			auto http_uri = package_handler->GetUriFromHttpPackage(http_content->str_http_content);
			if ( http_uri.first != http_uri.second )
			{
				std::string quest_method(http_method.first, http_method.second), quest_uri(http_uri.first, http_uri.second);
				
				//ִ�з�������
				auto call_res = g_pHttpSendCall.Call<enHttpSendCall_Result>(http_content, obj2, obj1, msg_size, 0);
				if ( GType::enHttpSendCall_Result_Succeed != call_res )
					return call_res;

				//ִ���հ�����
				HandleRecvPackage::stHttpQuestInfo quest = {
					quest_method, quest_uri
				};
				HandleRecvPackage::GetMe().DoSllRead(quest);
				return call_res;
			}
		}
	}
	return g_pHttpSendCall.Call<enHttpSendCall_Result>(http_content, obj2, obj1, msg_size, 0);*/
}

void GClass::HttpPackageSend::ReplaceMsg( const char* msg_head, const std::string& msg, GType::stHttpSendCall_Content* msg_src )
{
	if ( !msg_head || !msg_src || !msg_src->str_http_content )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�޸ķ����ж���ͨ��";
		return;
	}

	//��Ч��Ϣ�ĳ���
	const int kMsgSize = msg.size();
	const int kMsgHeadSize = strlen(msg_head);
	const auto kTotalLen = kMsgSize + kMsgHeadSize;

	char* str_buffer = (char*)MallocOfGame(kTotalLen + 1);
	if ( !str_buffer )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "MallocOfGame�����ڴ�ʧ��";
		return;
	}
	//�ͷ�ԭʼ��
	FreeOfGame((char*)msg_src->str_http_content);

	msg_src->str_http_content = str_buffer;
	msg_src->total_size_http_content = kTotalLen;

	CopyMemory(str_buffer, msg_head, kMsgHeadSize);
	str_buffer += kMsgHeadSize;
	CopyMemory(str_buffer, msg.c_str(), kMsgSize);
	str_buffer += kMsgSize;
	*str_buffer = '\0';
}

void GClass::HttpPackageSend::ReplaceMsg_Uri( const char* uri, const std::string& msg, GType::stHttpSendCall_Content& msg_src )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ж���ͨ��";
		return;
	}
	const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombineNormalMsgHead(uri, msg);
	ReplaceMsg(msg_head.c_str(), msg, &msg_src);
}

void GClass::HttpPackageSend::ReplaceMsg_Json( const char* uri, const Json::Value& msg, GType::stHttpSendCall_Content& msg_src )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�ж���ͨ��";
		return;
	}
	Json::FastWriter json_writer;
	const auto& str_msg = json_writer.write(msg);
	ReplaceMsg_Uri(uri, str_msg, msg_src);
}

GType::enHttpSendCall_Result GClass::HttpPackageSend::DoSend_Impl( const char* http_content, std::size_t content_size )
{
	auto& me = GetMe();
	if ( 0 != me.game_sending_ )
	{
		/*LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ�Ѿ��ڷ����ˣ��Լ��ķ�������֮,��ǰ����->" << me.game_sending_;*/
		me.RectifySendingCount();
		if ( 0 != me.game_sending_ )
			return GType::enHttpSendCall_Result_Fail;
	}
	assert(http_content);
	assert(content_size > 0);
	//�Լ��������Լ��հ�
	auto package_handler = HandleHttpPackage::GetInstance();
	if ( package_handler && FuncObj_NormalC::GetInstance() )
	{
		auto http_method = package_handler->GetMethodFromHttpPackage(http_content);
		if ( http_method.first != http_method.second )
		{
			auto http_uri = package_handler->GetUriFromHttpPackage(http_content);
			if ( http_uri.first != http_uri.second )
			{
				auto quest = std::make_shared<HandleRecvPackage::stHttpQuestInfo>();
				assert(quest);
				if ( !quest )
					return enHttpSendCall_Result_Fail;
				quest->method_.assign(http_method.first, http_method.second);
				quest->uri_.assign(http_uri.first, http_uri.second);

				auto ssl_handle = GFuncCall::GetSllReadHandle();
				if ( !ssl_handle )
				{
					LOG_ENTER_FUNC;
					LOG_O(Log_error) << "SSL_write,ssl_handleΪ��";
					return enHttpSendCall_Result_Fail;
				}
				auto write_size = g_pSSL_write.Call<int>(ssl_handle, http_content, content_size);
				if ( write_size <= 0 )
				{
					LOG_ENTER_FUNC;
					LOG_O(Log_error) << "SSL_write error, write size->" << write_size;
					return enHttpSendCall_Result_Fail;
				}

				//ִ���հ�����
				HandleRecvPackage::GetMe().DoSllRead(quest);
				return enHttpSendCall_Result_Succeed;
			}
		}
	}
	LOG_ENTER_FUNC;
	LOG_O(Log_error) << "SSL_writeδ֪��������";
	return enHttpSendCall_Result_Fail;
}

bool GClass::HttpPackageSend::SendGetMsgAsync( const char* uri )
{
	if ( !uri )
		return false;
	const auto& msg_head = HandleSendPackage::GetMe().HttpPackage_CombinePostMsgHead(uri);
	return GType::enHttpSendCall_Result_Succeed == SendHttpPackageAsync(msg_head.c_str(), "");
}

bool GClass::HttpPackageSend::Post_JsonMsgAsync( const char* uri, const Json::Value* msg )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return false;
	}

	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
		return false;

	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return false;

	auto request = std::make_shared<HTTPRequest_RFB>();
	if ( !request )
	{
		assert(false);
		return false;
	}
	auto ostr = std::make_shared<std::ostringstream>();
	if ( !ostr )
		return false;

	//������Ϣ
	request->setVersion(HTTPRequest_RFB::HTTP_1_1);
	request->setMethod(HTTPRequest_RFB::HTTP_POST);
	request->setURI(uri);
	request->setHost(handle_http->GetHost());
	request->add("Accept", "*/*");
	request->setCookies(handle_http->GetCookie());
	request->setKeepAlive(true);
	request->setContentType("application/json");
	
	std::string str_msg;
	if (msg)
	{
		Json::FastWriter json_writer;
		str_msg = json_writer.write(*msg);
	} 
	else
	{
		str_msg = "{}";
	}
	
	request->SetContent(str_msg);

	request->write(*ostr);

	gwnd->AsyncExec([=](){
		SendRequestImpl(ostr->str(), request);
	});
	return true;
}

bool GClass::HttpPackageSend::Get_JsonMsgAsync( const char* uri )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return false;
	}
	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return false;

	auto ostr = std::make_shared<std::ostringstream>();
	if ( !ostr )
		return false;

	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
		return false;

	auto request = std::make_shared<HTTPRequest_RFB>();
	if ( !request )
	{
		assert(false);
		return false;
	}

	//������Ϣ
	request->setVersion(HTTPRequest_RFB::HTTP_1_1);
	request->setMethod(HTTPRequest_RFB::HTTP_GET);
	request->setURI(uri);
	request->setHost(handle_http->GetHost());
	request->add("Accept", "*/*");
	request->setCookies(handle_http->GetCookie());
	request->setKeepAlive(true);
	
	request->write(*ostr);

	gwnd->AsyncExec([=](){
		SendRequestImpl(ostr->str(), request);
	});
	return true;
}

void GClass::HttpPackageSend::SendRequestImpl( const std::string& http_package, const std::shared_ptr<HTTPRequest_RFB>& request )
{
	auto& me = GetMe();
	if ( 0 != me.game_sending_ )
	{
		/*LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ�Ѿ��ڷ����ˣ��Լ��ķ�������֮,��ǰ����->" << me.game_sending_;*/
		me.RectifySendingCount();
		if ( 0 != me.game_sending_ )
			return;
	}
	auto ssl_handle = GFuncCall::GetSllReadHandle();
	if ( !ssl_handle )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "SSL_write,ssl_handleΪ��";
		return;
	}
	auto write_size = g_pSSL_write.Call<int>(ssl_handle, http_package.c_str(), http_package.size());
	if ( write_size <= 0 )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "SSL_write error, write size->" << write_size;
		return;
	}

	//ִ���հ�����
	HandleRecvPackage::GetMe().DoRequest_SllRead(request);
}

bool GClass::HttpPackageSend::Post_EncryptJsonMsgAsync( const char* uri, const Json::Value& msg )
{
	if ( !uri )
	{
		assert(false);
		return false;
	}
	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
		return false;

	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return false;

	auto request = std::make_shared<HTTPRequest_RFB>();
	if ( !request )
	{
		assert(false);
		return false;
	}
	auto ostr = std::make_shared<std::ostringstream>();
	if ( !ostr )
		return false;

	//������Ϣ
	request->setVersion(HTTPRequest_RFB::HTTP_1_1);
	request->setMethod(HTTPRequest_RFB::HTTP_POST);
	request->setURI(uri);
	request->setHost(handle_http->GetHost());
	request->add("Accept", "*/*");
	request->setCookies(handle_http->GetCookie());
	request->setKeepAlive(true);
	request->setContentType("application/x-gzip");
	request->EnJsonContentAsGzip(msg);

	request->write(*ostr);

	gwnd->AsyncExec([=](){
		SendRequestImpl(ostr->str(), request);
	});
	return true;
}

bool GClass::HttpPackageSend::Get_JsonMsgSync( const char* uri, Json::Value& respond_msg )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return false;
	}
	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
	{
		assert(false);
		return false;
	}

	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
	{
		assert(false);
		return false;
	}

	HTTPRequest_RFB request;

	//������Ϣ
	request.setVersion(HTTPRequest_RFB::HTTP_1_1);
	request.setMethod(HTTPRequest_RFB::HTTP_GET);
	request.setURI(uri);
	request.setHost(handle_http->GetHost());
	request.add("Accept", "*/*");
	request.setCookies(handle_http->GetCookie());
	request.setKeepAlive(true);
	
	std::ostringstream ostr;
	request.write(ostr);

	std::shared_ptr<HTTPResponse_RFB> respond;
	gwnd->SyncExec([&](){
		SendRequestImplSync(ostr.str(), respond);
	});
	if ( !respond )
	{
		//assert(false);
		return false;
	}
	if ( !respond->ContentTypeIsJson() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "content type is not json";
		return false;
	}
	if ( !respond->DeContentToJson(respond_msg) )
	{
		assert(false);
		return false;
	}
	return true;
}

void GClass::HttpPackageSend::SendRequestImplSync( const std::string& http_package, std::shared_ptr<HTTPResponse_RFB>& respond )
{
	auto& me = GetMe();
	if ( 0 != me.game_sending_ )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "��Ϸ�Ѿ��ڷ����ˣ��Լ��ķ�������֮,��ǰ����->" << me.game_sending_;
		me.RectifySendingCount();
		if ( 0 != me.game_sending_ )
			return;
	}
	auto ssl_handle = GFuncCall::GetSllReadHandle();
	if ( !ssl_handle )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "SSL_write,ssl_handleΪ��";
		return;
	}
	auto write_size = g_pSSL_write.Call<int>(ssl_handle, http_package.c_str(), http_package.size());
	if ( write_size <= 0 )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "SSL_write error, write size->" << write_size;
		return;
	}

	//ִ���հ�����
	HandleRecvPackage::GetMe().DoRequest_SllReadSync(respond);
}

bool GClass::HttpPackageSend::Post_JsonMsgSync( const char* uri, const Json::Value* msg, Json::Value& respond_msg )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return false;
	}
	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return false;

	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
		return false;

	HTTPRequest_RFB request;

	//������Ϣ
	request.setVersion(HTTPRequest_RFB::HTTP_1_1);
	request.setMethod(HTTPRequest_RFB::HTTP_POST);
	request.setURI(uri);
	request.setHost(handle_http->GetHost());
	request.add("Accept", "*/*");
	request.setCookies(handle_http->GetCookie());
	request.setKeepAlive(true);
	request.setContentType("application/json");
	
	std::string str_msg;
	if (msg)
	{
		Json::FastWriter json_writer;
		str_msg = json_writer.write(*msg);
	} 
	else
	{
		str_msg = "{}";
	}
	request.SetContent(str_msg);

	std::ostringstream ostr;
	request.write(ostr);

	std::shared_ptr<HTTPResponse_RFB> respond;
	gwnd->SyncExec([&](){
		SendRequestImplSync(ostr.str(), respond);
	});
	if ( !respond )
		return false;
	if ( !respond->ContentTypeIsJson() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "content type is not json";
		return false;
	}
	return respond->DeContentToJson(respond_msg);
}

bool GClass::HttpPackageSend::Post_EncryptJsonMsgSync( const char* uri, const Json::Value& msg, Json::Value& respond_msg )
{
	if ( !uri )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "uri����Ϊ��";
		return false;
	}
	auto gwnd = FuncObj_NormalC::GetGWnd();
	if ( !gwnd )
		return false;

	auto handle_http = HandleHttpPackage::GetInstance();
	if ( !handle_http )
		return false;

	HTTPRequest_RFB request;

	//������Ϣ
	request.setVersion(HTTPRequest_RFB::HTTP_1_1);
	request.setMethod(HTTPRequest_RFB::HTTP_POST);
	request.setURI(uri);
	request.setHost(handle_http->GetHost());
	request.add("Accept", "*/*");
	request.setCookies(handle_http->GetCookie());
	request.setKeepAlive(true);
	request.setContentType("application/x-gzip");
	request.EnJsonContentAsGzip(msg);

	std::ostringstream ostr;
	request.write(ostr);

	std::shared_ptr<HTTPResponse_RFB> respond;
	gwnd->SyncExec([&](){
		SendRequestImplSync(ostr.str(), respond);
	});
	if ( !respond )
		return false;
	if ( !respond->ContentTypeIsJson() )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "content type is not json";
		return false;
	}
	return respond->DeContentToJson(respond_msg);
}

void GClass::HttpPackageSend::BeginSendHttp()
{
	++game_sending_;
	/*LOG_ENTER_FUNC;
	LOG_O(Log_trace) << "��Ϸ��ʼ����,��ǰ����->" << game_sending_;*/
}

void GClass::HttpPackageSend::EndRecvHttp()
{
	--game_sending_;
	
	LOG_ENTER_FUNC;
	/*if ( game_sending_ < 0 )
	{
		LOG_O(Log_warning) << "��Ϸ����������������Ȼ����0������Ϊ0, ����Ϊ->" << game_sending_;
		game_sending_ = 0;
	}
	else
	{
		LOG_O(Log_trace) << "��Ϸ��������,��ǰ����->" << game_sending_;
	}
	assert(game_sending_ >= 0);*/

	if ( false && 0 != game_sending_ && game_sending_ == rectify_send_count_.first )
	{
		++rectify_send_count_.second;
		LOG_O(Log_info) << "������Ϸ�еķ�����������Ϸ�еĵ�ǰ����->" << game_sending_ << "\t��ǰ��ײ����->" << rectify_send_count_.second;
	}
	else
	{
		//LOG_O(Log_trace) << "��Ϸ��������,��ǰ����->" << game_sending_;
	}
}

void GClass::HttpPackageSend::RectifySendingCount()
{
	return;
	{
		if ( 0 == game_sending_ )
		{
			assert(!"Ϊ0�Ļ����Ͳ���ִ���������");
			return;
		}
		WriteLock wl(reset_sending_mutex_);
		if (reset_sending_cnt_)
		{
			game_sending_ = 0;
			reset_sending_cnt_ = false;
		}
	}
}

void GClass::HttpPackageSend::ResetSendCount()
{
	return;
	WriteLock wl(reset_sending_mutex_);
	reset_sending_cnt_ = true;
}

void GClass::HttpPackageSend::SendPackageHit()
{
	auto func_obj = FuncObj_NormalC::GetInstance();
	if ( !func_obj )
		return;
	auto gwnd = func_obj->GetGWnd();
	if ( !gwnd )
		return;
	gwnd->SyncExec([this](){
		if ( 0 == game_sending_ )
			return;

		if ( game_sending_ == rectify_send_count_.first )
		{
			//����֮
			if ( rectify_send_count_.second >= 5 )
			{
				DateTimeLocal time_now;
				auto time_span = time_now - last_rec_time_;
				if ( time_span.totalSeconds() < 45 )
				{
					//rectify_send_count_.first = 0;
					rectify_send_count_.second = 0;
					return;
				}

				game_sending_ = 0;
				rectify_send_count_.first = 0;
				rectify_send_count_.second = 0;
			}
			else
			{
				++rectify_send_count_.second;
				LOG_ENTER_FUNC;
				LOG_O(Log_info) << "������Ϸ�еķ�����������Ϸ�еĵ�ǰ����->" << game_sending_ << "\t��ǰ��ײ����->" << rectify_send_count_.second;
			}
		}
		else
		{
			rectify_send_count_.first = game_sending_;
			rectify_send_count_.second = 0;
			last_rec_time_ = DateTimeLocal();
		}
	});
}

GClass::HandleRecvPackage::HandleRecvPackage()
{
}

HandleRecvPackage& GClass::HandleRecvPackage::GetMe()
{
	static HandleRecvPackage handle_recv;
	return handle_recv;
}

void GClass::HandleRecvPackage::RecvHttpPackage( const char* str_http, int package_length )
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj normal��Ȼ��δ����";
		return;
	}
	auto inject = func_obj_normal->GetInterInject();
	if ( !inject )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj inject��Ȼ��δ����";
		return;
	}

	const auto kContentLen = GetContentLength(str_http);
	if (kContentLen <= 0)
	{
		/*assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�յ��İ����Ҳ���ContentLength";
		return;*/
		//goto LABEL_NEXT;
		//assert(false);
		return;
	}
	auto head_size = GetHttpHeaderLength(str_http, package_length);
	if (head_size <= 0)
		return;
	auto this_msg_len = package_length - head_size;
	if (this_msg_len > kContentLen)
	{
		assert(false);
		return;
	}
	else if (this_msg_len == kContentLen)
	{
		std::shared_ptr<std::string> str_http_copy(new std::string(str_http, package_length));
		assert(str_http_copy->size() == package_length);
		inject->AsyncExec([=](){
			this->RecvHttpPackageParse(*str_http_copy);
		});
		return;
	}
	else
	{
		WriteLock write_lock(mutex_handle_follow_);
		sequents_.push(Sequent());
		/*LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "��Ϸ�߳�Ҫpush��";*/
		auto& anterior = sequents_.back();
		anterior.str_anterior_.assign(str_http, package_length);
		anterior.left_package_len_ = kContentLen - this_msg_len;
		return;
	}
	/*
	//this msg length
	const auto kHttpMsgLen = GetHttpMsgLength(str_http, package_length);
	if ( 0 == kHttpMsgLen )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�յ��İ���MsgLength��ȻΪ0";
		return;
	}
	if ( kContentLen > kHttpMsgLen )
		//���к����İ����������Ϸ�߳��ﴦ����
	{
		auto first_tag_addr = GetFirstTagCharAddr(str_http, package_length);
		if ( !first_tag_addr )
		{
			assert(false);
			LOG_O(Log_error) << "������Ǹ��к����İ����յ��İ��о�Ȼ�Ҳ����׸�tag�ĵ�ַ";
			return;
		}
		WriteLock write_lock(mutex_handle_follow_);
		sequents_.push(Sequent());
		auto& anterior = sequents_.back();
		anterior.str_anterior_.assign(str_http, first_tag_addr);
		anterior.left_package_len_ = kContentLen - kHttpMsgLen;
		return;
	}

LABEL_NEXT:
	std::string str_http_copy(str_http, package_length);
	assert(str_http_copy.size() == package_length);
	inject->AsyncExec([=](){
		this->RecvHttpPackageParse(str_http_copy);
	});*/
}

void GClass::HandleRecvPackage::HandleFollowPackage( const char* str_follow, size_t package_length )
{
	{
		ReadLock read_lock(mutex_handle_follow_);
		if (sequents_.empty())
			return;
	}

	/*if ( !IsSpecifyZeroTag(str_follow, package_length) )
		return;*/

	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj normal��Ȼ��δ����";
		return;
	}
	auto inject = func_obj_normal->GetInterInject();
	if ( !inject )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj inject��Ȼ��δ����";
		return;
	}

	std::shared_ptr<std::string> str_follow_copy(new std::string(str_follow, package_length));
	assert(str_follow_copy->size() == package_length);
	inject->AsyncExec([=](){
		this->FollowPackageParse(*str_follow_copy);
	});
}

int GClass::HandleRecvPackage::GetContentLength( const char* str_http )
{
	static const auto kStrFind = "Content-Length:";
	static int kStrLen = strlen(kStrFind);
	
	auto it = strstr(str_http, kStrFind);
	if ( !it )
		return -1;
	it += kStrLen;
	return (size_t)atoi(it);
}

size_t GClass::HandleRecvPackage::GetHttpMsgLength( const char* str_http, size_t package_length )
{
	/*auto first_tag_addr = GetFirstTagCharAddr(str_http, package_length);
	if ( !first_tag_addr )
		return 0;*/
	auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(str_http);
	if ( !first_msg_char_addr )
		return 0;
	return std::distance(first_msg_char_addr, str_http + package_length);
}

size_t GClass::HandleRecvPackage::GetFollowMsgLength( const char* str_follow, size_t package_length )
{
	return package_length;
	/*auto first_tag_addr = GetFirstTagCharAddr(str_follow, package_length);
	if ( !first_tag_addr )
		return 0;
	return std::distance(str_follow, first_tag_addr);*/
}

const char* GClass::HandleRecvPackage::GetFirstTagCharAddr( const char* str_package, size_t package_length )
{
	//�ѱ�����
	assert(false);
	if ( !IsSpecifyZeroTag(str_package, package_length) )
	{
		assert(false);
		return nullptr;
	}
	//���Ľ�β����0�ĸ���
	const BYTE kZeroCnt = *(BYTE*)(str_package + package_length - 1);
	return str_package + package_length - kZeroCnt - sizeof(kZeroCnt) - 20;
}

bool GClass::HandleRecvPackage::IsSpecifyZeroTag( const char* str_package, size_t package_length )
{
	return true;
	auto last_zero = str_package + package_length - 1;
	const BYTE kZeroCnt = *last_zero;
	--last_zero;
	for ( BYTE i = 0;i != kZeroCnt; ++i, --last_zero )
	{
		if ( 0 != *last_zero )
			return false;
	}
	return true;
}

const char* GClass::HandleHttpPackage::GetFirstHttpMsgCharAddr( const char* str_http )
{
	auto find_str = strstr(str_http, "\r\n\r\n");
	if ( find_str )
		return find_str + 4;
	find_str = strstr(str_http, "\r\r\n\r\r\n");
	if (find_str)
		return find_str + 6;
	return nullptr;
}

void GClass::HandleRecvPackage::HandleFullRecvPackage( const std::string& msg_head, const std::string& msg )
{
	//LOG_ENTER_FUNC;
#ifdef D_SOME_LOG
	LOG_O(Log_trace) << "�յ�������Ϣͷ�ǣ�" << msg_head;
	//LOG_O(Log_trace) << "�յ�������Ϣ�ǣ�" << msg;
#endif
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return;
	Json::Value root;
	auto& glua = func_obj_normal->GetGLua();
	if ( !JsonReader::GetMe().ParseCStr(msg.c_str(), root) )
	{
		glua.LuaObjCall<void>("HandleRecvHttpPackage", msg_head.c_str());
	}
	else
	{
		glua.LuaObjCall<void>("HandleRecvHttpPackage", msg_head.c_str(), &root);
	}
	//return;
	static bool is_version_end_time = false;
	if (is_version_end_time)
		return;
	HTTPResponse_RFB respond;
	if ( !respond.ReadFromBuffer(msg_head) )
	{
		assert(false);
		return;
	}
	if ( !respond.has(HTTPResponse_RFB::DATE) )
		return;
	auto timest = respond.getDate();
	DateTimeLocal dt_now(timest);
	dt_now.makeLocal(GetTzd());
	static const DateTimeLocal end_time(kVersionEndTime_Year, kVersionEndTime_Month, kVersionEndTime_Day);
	//auto str = Poco::DateTimeFormatter::format(dt_now, Poco::DateTimeFormat::SORTABLE_FORMAT);
	if ( dt_now >= end_time )
	{
		assert(false);
		is_version_end_time = true;
		LOG_O(Log_warning) << "version is end time";
		SetIoTimer(2 * 1000, []( IoTimer* ){
			auto func_obj_normal = FuncObj_NormalC::GetInstance();
			if ( !func_obj_normal )
				return;
			auto& session_oper = func_obj_normal->GetSessionOper();
			bool res = false;
			session_oper.ToCall(BC_MakeP("ved"));
			auto& glua = func_obj_normal->GetGLua();
			glua.LuaObjCall<void>("MixLua");
		});
	}
}

void GClass::HandleRecvPackage::RecvHttpPackageParse( const std::string& _str_http )
{
	auto str_http = _str_http.c_str();
	const auto package_length = _str_http.size();

#ifdef false
	{
		const auto kContentLen = GetContentLength(str_http);

		//this msg length
		const auto kHttpMsgLen = GetHttpMsgLength(str_http, package_length);

		if ( kContentLen != kHttpMsgLen )
		{
			assert(false);
			LOG_ENTER_FUNC;
			LOG_O(Log_fatal) << "������kContentLen������kHttpMsgLen��������϶������������";
			return;
		}
	}
#endif
	
	/*auto first_tag_addr = GetFirstTagCharAddr(str_http, package_length);
	if ( !first_tag_addr )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "������Ǹ������İ����յ��İ��о�Ȼ�Ҳ����׸�tag�ĵ�ַ";
		return;
	}*/
	auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(str_http);
	if ( !first_msg_char_addr )
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�յ��İ��о�Ȼ�Ҳ����׸�Http msg�ַ��ĵ�ַ";
		return;
	}

	/*//����
	char old_char = *first_tag_addr;
	//��β��0
	*const_cast<char*>(first_tag_addr) = '\0';*/
	//utf-8תGBK
	const std::string& gbk_msg = Utf8ToGbk(first_msg_char_addr);
	//�ָ�
	//*const_cast<char*>(first_tag_addr) = old_char;

	std::string msg_head(str_http, first_msg_char_addr);
	assert(!msg_head.empty());

	HandleFullRecvPackage(msg_head, gbk_msg);
}

void GClass::HandleRecvPackage::FollowPackageParse( const std::string& _str_follow )
{
	/*{
		ReadLock read_lock(mutex_handle_follow_);
		if (sequents_.empty())
			return;
	}*/
	LOG_ENTER_FUNC;

	auto str_follow = _str_follow.c_str();
	const auto package_length = (int)_str_follow.size();

	/*if ( !IsSpecifyZeroTag(str_follow, package_length) )
	{
		assert(false);
		LOG_O(Log_error) << "�����������У�����tag��־��Ȼ��Ϊ0����־�ȶԲ���ȷ";
		return;
	}*/

	WriteLock write_lock(mutex_handle_follow_);
	if (sequents_.empty())
		return;
	auto& anterior = sequents_.front();
	if ( package_length > anterior.left_package_len_ )
	{
		LOG_O(Log_error).operator<< ("�����������У���ǰ�İ����Ⱦ�Ȼ����ʣ��İ����ȣ�ʲô����� ��������Ե��ĺ������������ǣ�")
			.write(str_follow, package_length);
		sequents_.pop();
		return;
	}

	anterior.left_package_len_ -= package_length;
	//LOG_O(Log_trace) << "�������Ĵ����У�Ҫappend�ַ����ˣ�sequents.size==" << sequents_.size() << "append֮ǰ��" << anterior.str_anterior_;
	anterior.str_anterior_.append(str_follow, package_length);
	//LOG_O(Log_trace) << "�������Ĵ����У�Ҫappend�ַ����ˣ�append֮��" << anterior.str_anterior_;
	if ( 0 == anterior.left_package_len_ )
	{
		auto func_obj_normal = FuncObj_NormalC::GetInstance();
		if ( !func_obj_normal )
		{
			LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj normal��Ȼ��δ����";
			sequents_.pop();
			return;
		}
		auto inject = func_obj_normal->GetInterInject();
		if ( !inject )
		{
			assert(false);
			LOG_O(Log_fatal) << "�Ѿ��հ��ˣ�func obj inject��Ȼ��δ����";
			sequents_.pop();
			return;
		}

		auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(anterior.str_anterior_.c_str());
		if ( !first_msg_char_addr )
		{
			assert(false);
			LOG_O(Log_fatal) << "��Ȼ�Ҳ���{���������ǣ�" << anterior.str_anterior_;
			sequents_.pop();
			return;
		}
		auto str_begin = &*anterior.str_anterior_.begin();
		std::string msg_head(str_begin, first_msg_char_addr);
		assert(!msg_head.empty());
		//utf8 to gbk
		const auto& msg_utf8 = Utf8ToGbk(first_msg_char_addr);

		//LOG_O(Log_trace) << "�����������У�Ҫpop��";
		sequents_.pop();
		write_lock.unlock();
		HandleFullRecvPackage(msg_head, msg_utf8);
	}
}

void GClass::HandleRecvPackage::OnRecvHttpResult( const std::shared_ptr<stHttpQuestInfo>& quest, const HTTPResponse_RFB& respond )
{
	assert(quest);
	if (respond.ContentTypeIsJson())
	{
		Json::Value result_msg;
		if ( !respond.DeContentToJson(result_msg) )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << "ת����jsonʧ��";
			return;
		}
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "�Լ�������Ȼ���Լ��յ��˰���quest method->" << quest->method_ << "\turi->" << quest->uri_;
			//<< "respond, real msg->" << respond.GetRealMsg();

		OnRecvJsonResult(quest, result_msg);
		return;
	}

	LOG_ENTER_FUNC;
	LOG_O(Log_warning) << "�յ���http���л���������ʽ�����ݣ������ʾ���ع�ע";
}

void GClass::HandleRecvPackage::OnRecvJsonResult( const std::shared_ptr<stHttpQuestInfo>& quest, const Json::Value& result_msg )
{
	if ( !quest )
	{
		assert(false);
		return;
	}
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return;
	func_obj_normal->GetGLua().LuaObjCall<void>("HandleSendRecvMap", *quest, result_msg);
}

void GClass::HandleRecvPackage::DoSllRead( const std::shared_ptr<stHttpQuestInfo>& quest )
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return;
	auto inject = func_obj_normal->GetInterInject();
	if ( !inject )
		return;
	
	LOG_ENTER_FUNC;
	//ssl handle
	auto ssl_handle = GFuncCall::GetSllReadHandle();
	if ( !ssl_handle )
	{
		LOG_O(Log_error) << "ssl handle��ȻΪ0���ѵ���δ������ͨ��?";
		return;
	}
	/*auto read_size = g_pSSL_read.Call<int>(ssl_handle, buffer, sizeof(buffer));
	if ( -1 != read_size )
	{
		LOG_O(Log_error) << "��һ��SSL_read���ص�ֵ��->" << read_size;
		return;
	}
	read_size = g_pSSL_read.Call<int>(ssl_handle, buffer, sizeof(buffer));
	if ( read_size <= 0 )
	{
		LOG_O(Log_error) << "�ڶ���SSL_read���ص�ֵ��->" << read_size;
		return;
	}*/
	int read_size = -1, ssl_err = -1;
	//for ( auto cnt = 0;cnt != 5; ++cnt )
	while (true)
	{
		read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
		if ( read_size > 0 )
			break;
		ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
		if ( SSL_ERROR_WANT_READ != ssl_err )
			break;
		::Sleep(0);
	}
	if ( read_size <= 0 )
	{
		LOG_O(Log_error) << "SSL_read��ȡ�ʼ��������ʧ��1, read size->" << read_size << "\tssl error(-1��ʾ������ֵ�ǲ�׼��)->" << ssl_err;
		return;
	}
	
	auto respond = std::make_shared<HTTPResponse_RFB>();
	if ( !respond )
	{
		assert(false);
		LOG_O(Log_fatal) << "new HTTPResponse_RFBʧ��";
		return;
	}
	if ( !respond->ReadFromBuffer(ssl_read_buffer, read_size) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "ReadFromBuffer����";
		return;
	}
	
	const auto kContentLen = respond->getContentLength();

	if ( kContentLen != -1 )
	{
		//��ȡ�����İ�
		while ( respond->GetRealMsg().size() < kContentLen )
		{
			read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
			if ( read_size > 0 )
			{
				respond->AddContent(ssl_read_buffer, read_size);
				continue;
			}
			ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
			if ( SSL_ERROR_WANT_READ != ssl_err )
				break;
			::Sleep(0);
		}

		const auto kTotalSize = respond->GetRealMsg().size();
		if ( kTotalSize != kContentLen )
		{
			LOG_O(Log_error) << "SSL_read�õ��������İ�����Ϣ���ݵĳ���->" << kTotalSize << "\t��Content-length->" << kContentLen
				<< "\tssl err->" << ssl_err << "\treal msg->" << respond->GetRealMsg();
			return;
		}
	}

	inject->AsyncExec([=](){
		assert(respond);
		if ( !respond )
			return;
		OnRecvHttpResult(quest, *respond);
	});
}

void GClass::HandleRecvPackage::DoRequest_SllRead( const std::shared_ptr<HTTPRequest_RFB>& quest )
{
	if ( !quest )
	{
		assert(false);
		return;
	}
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return;
	auto inject = func_obj_normal->GetInterInject();
	if ( !inject )
		return;
	
	LOG_ENTER_FUNC;
	//ssl handle
	auto ssl_handle = GFuncCall::GetSllReadHandle();
	if ( !ssl_handle )
	{
		LOG_O(Log_error) << "ssl handle��ȻΪ0���ѵ���δ������ͨ��?";
		return;
	}

	int read_size = -1, ssl_err = -1;
	//for ( auto cnt = 0;cnt != 5; ++cnt )
	while (true)
	{
		read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
		if ( read_size > 0 )
			break;
		ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
		if ( SSL_ERROR_WANT_READ != ssl_err )
			break;
		::Sleep(0);
	}
	if ( read_size <= 0 )
	{
		LOG_O(Log_error) << "SSL_read��ȡ�ʼ��������ʧ��2, read size->" << read_size << "\tssl error(-1��ʾ������ֵ�ǲ�׼��)->" << ssl_err;
		return;
	}
	
	auto respond = std::make_shared<HTTPResponse_RFB>();
	if ( !respond )
	{
		assert(false);
		LOG_O(Log_fatal) << "new HTTPResponse_RFBʧ��";
		return;
	}
	if ( !respond->ReadFromBuffer(ssl_read_buffer, read_size) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "ReadFromBuffer����";
		return;
	}
	
	const auto kContentLen = respond->getContentLength();
	if ( kContentLen != -1 )
	{
		//��ȡ�����İ�
		while ( respond->GetRealMsg().size() < kContentLen )
		{
			read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
			if ( read_size > 0 )
			{
				respond->AddContent(ssl_read_buffer, read_size);
				continue;
			}
			ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
			if ( SSL_ERROR_WANT_READ != ssl_err )
				break;
			::Sleep(0);
		}

		const auto kTotalSize = respond->GetRealMsg().size();
		if ( kTotalSize != kContentLen )
		{
			LOG_O(Log_error) << "SSL_read�õ��������İ�����Ϣ���ݵĳ���->" << kTotalSize << "\t��Content-length->" << kContentLen
				<< "\tssl err->" << ssl_err << "\treal msg->" << respond->GetRealMsg();
			return;
		}
	}

	inject->AsyncExec([=](){
		assert(respond);
		if ( !respond )
			return;
		OnRequestHttpResult(*quest, *respond);
	});
}

void GClass::HandleRecvPackage::OnRequestHttpResult( const HTTPRequest_RFB& quest, const HTTPResponse_RFB& respond )
{
	if (respond.ContentTypeIsJson())
	{
		Json::Value result_msg;
		if ( !respond.DeContentToJson(result_msg) )
		{
			LOG_ENTER_FUNC;
			LOG_O(Log_error) << "ת����jsonʧ��";
			return;
		}
		LOG_ENTER_FUNC;
		LOG_O(Log_trace) << "�Լ�������Ȼ���Լ��յ��˰���quest method->" << quest.getMethod() << "\turi->" << quest.getURI();
		//<< "respond, real msg->" << respond.GetRealMsg();

		OnRequestJsonResult(quest, result_msg);
		return;
	}

	LOG_ENTER_FUNC;
	LOG_O(Log_warning) << "�յ���http���л���������ʽ�����ݣ������ʾ���ع�ע";
}

void GClass::HandleRecvPackage::OnRequestJsonResult( const HTTPRequest_RFB& quest, const Json::Value& result_msg )
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
		return;
	func_obj_normal->GetGLua().LuaObjCall<void>("HandleRequestRecvMap", &quest, &result_msg);
}

void GClass::HandleRecvPackage::DoRequest_SllReadSync( std::shared_ptr<HTTPResponse_RFB>& respond )
{
	auto func_obj_normal = FuncObj_NormalC::GetInstance();
	if ( !func_obj_normal )
	{
		assert(false);
		return;
	}
	auto inject = func_obj_normal->GetInterInject();
	if ( !inject )
	{
		assert(false);
		return;
	}
	
	LOG_ENTER_FUNC;
	//ssl handle
	auto ssl_handle = GFuncCall::GetSllReadHandle();
	if ( !ssl_handle )
	{
		LOG_O(Log_error) << "ssl handle��ȻΪ0���ѵ���δ������ͨ��?";
		assert(false);
		return;
	}

	int read_size = -1, ssl_err = -1;
	while (true)
	{
		read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
		if ( read_size > 0 )
			break;
		ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
		if ( SSL_ERROR_WANT_READ != ssl_err )
			break;
		::Sleep(0);
	}
	if ( read_size <= 0 )
	{
		LOG_O(Log_error) << "SSL_read��ȡ�ʼ��������ʧ��3, read size->" << read_size << "\tssl error(-1��ʾ������ֵ�ǲ�׼��)->" << ssl_err;
		return;
	}
	if ( !respond )
		respond = std::make_shared<HTTPResponse_RFB>();
	if ( !respond )
	{
		assert(false);
		LOG_O(Log_fatal) << "new HTTPResponse_RFBʧ��";
		return;
	}
	if ( !respond->ReadFromBuffer(ssl_read_buffer, read_size) )
	{
		LOG_ENTER_FUNC;
		LOG_O(Log_warning) << "ReadFromBuffer����";
		return;
	}
	
	const auto kContentLen = respond->getContentLength();
	if ( kContentLen == -1 )
	{
		LOG_O(Log_debug) << "recv content len->-1";
		return;
	}
	//��ȡ�����İ�
	while ( respond->GetRealMsg().size() < kContentLen )
	{
		read_size = g_pSSL_read.Call<int>(ssl_handle, ssl_read_buffer, sizeof(ssl_read_buffer));
		if ( read_size > 0 )
		{
			respond->AddContent(ssl_read_buffer, read_size);
			continue;
		}
		ssl_err = g_pSSL_get_error.Call<int>(ssl_handle, read_size);
		if ( SSL_ERROR_WANT_READ != ssl_err )
			break;
		::Sleep(0);
	}
	
	const auto kTotalSize = respond->GetRealMsg().size();
	if ( kTotalSize != kContentLen )
	{
		LOG_O(Log_error) << "SSL_read�õ��������İ�����Ϣ���ݵĳ���->" << kTotalSize << "\t��Content-length->" << kContentLen
			<< "\tssl err->" << ssl_err << "\treal msg->" << respond->GetRealMsg();
		respond.reset();
		return;
	}
}

int GClass::HandleRecvPackage::GetHttpHeaderLength(const char* str_http, int package_length)
{
	auto first_msg_char_addr = HandleHttpPackage::GetFirstHttpMsgCharAddr(str_http);
	if (!first_msg_char_addr)
	{
		assert(false);
		LOG_ENTER_FUNC;
		LOG_O(Log_error) << "�յ��İ��о�Ȼ�Ҳ����׸�Http msg�ַ��ĵ�ַ112";
		return 0;
	}
	auto res = first_msg_char_addr - str_http;
	if (res > 0 && res <= package_length)
		return res;
	assert(false);
	return -1;
}

HandleHttpPackage* GClass::HandleHttpPackage::handler_ = nullptr;

HandleHttpPackage* GClass::HandleHttpPackage::GetInstance()
{
	return handler_;
}

GClass::HandleHttpPackage::HandleHttpPackage()
{
	assert(!handler_);
	handler_ = this;
}

const char* GClass::HandleHttpPackage::Post()
{
	return "POST ";
}

const char* GClass::HandleHttpPackage::HttpVersion()
{
	return " HTTP/1.1\r\n";
}

const char* GClass::HandleHttpPackage::Host( const char* http_package /*= nullptr */ )
{
	static HttpPackageParser helper("Host: ", "\r\n");
	if (http_package)
	{
		helper.ParseHost(http_package);
	}
	return helper.str_c_result_;
}

const char* GClass::HandleHttpPackage::Accept()
{
	return "\r\nAccept: */*\r\n";
}

const char* GClass::HandleHttpPackage::Cookie( const char* http_package /*= nullptr */ )
{
	static HttpPackageParser helper("Cookie: ", "\r\n");
	if (http_package)
	{
		helper.ParsePackage(http_package);
	}
	return helper.str_c_result_;
}

const char* GClass::HandleHttpPackage::Connection()
{
	return "\r\nConnection: Keep-Alive\r\n";
}

const char* GClass::HandleHttpPackage::ContentType()
{
	return "Content-Type: application/json\r\n";
}

void GClass::HandleHttpPackage::UpdateHandler( const char* http_package )
{
	static HandleHttpPackage handler;
	handler.Host(http_package);
	handler.Cookie(http_package);
}

GClass::HandleHttpPackage::~HandleHttpPackage()
{
	handler_ = nullptr;
}

bool GClass::HandleHttpPackage::ContentTypeIsJson( const char* str_http )
{
	auto first_occur = strstr(str_http, "Content-Type:");
	if (first_occur)
		return !!strstr(first_occur, "application/json");
	return false;
}

const char* GClass::HandleHttpPackage::ContentGzipType()
{
	return "Content-Type: application/x-gzip\r\n";
}

bool GClass::HandleHttpPackage::ContentTypeIsXgzip( const char* str_http )
{
	auto first_occur = strstr(str_http, "Content-Type:");
	if (first_occur)
		return !!strstr(first_occur, "application/x-gzip");
	return false;
}

FindBetweenStringA::RangePtr GClass::HandleHttpPackage::GetMethodFromHttpPackage( const char* http_package ) const
{
	auto it = strchr(http_package, ' ');
	if (it)
	{
		return FindBetweenStringA::RangePtr(http_package, it);
	}
	return FindBetweenStringA::RangePtr(nullptr, nullptr);
}

FindBetweenStringA::RangePtr GClass::HandleHttpPackage::GetUriFromHttpPackage( const char* http_package ) const
{
	auto it = strchr(http_package, ' ');
	if (it)
	{
		++it;
		auto it_end = strchr(it, ' ');
		if (it_end)
		{
			return FindBetweenStringA::RangePtr(it, it_end);
		}
	}
	return FindBetweenStringA::RangePtr(nullptr, nullptr);
}

const char* GClass::HandleHttpPackage::Get()
{
	return "GET ";
}

void GClass::HandleHttpPackage::SetHost( const std::string& str_host )
{
	if ( str_host != host_ )
	{
		if ( 0 == atoi(str_host.c_str()) )
			return;
		host_ = str_host;
	}
}

const std::string& GClass::HandleHttpPackage::GetHost() const
{
	return host_;
}

void GClass::HandleHttpPackage::SetCookie( const Poco::Net::NameValueCollection& cookie )
{
	cookie_ = cookie;
}

Poco::Net::NameValueCollection& GClass::HandleHttpPackage::GetCookie()
{
	return cookie_;
}

const std::string& GClass::HandleRecvPackage::stHttpQuestInfo::GetMethod() const
{
	return method_;
}

void GClass::HandleRecvPackage::stHttpQuestInfo::SetMethod( const std::string& method )
{
	method_ = method;
}

const std::string& GClass::HandleRecvPackage::stHttpQuestInfo::GetUri() const
{
	return uri_;
}

void GClass::HandleRecvPackage::stHttpQuestInfo::SetUri( const std::string& uri )
{
	uri_ = uri;
}
