--dofile==ÿ�ζ�Ҫ���롣loadfile==ֻ����(����)�ļ�һ��
--require�����μ���ͬһ���ļ���

__g_lua_files__ = {
	"Test", "Logic", "Tasks", "Logic_GWnd", "HandleAmbient",
	"Scri_Commands", "SendRecvMap",
	"GameStateSetter"
};

--set lua path
package.path = GetLuaDirectory() .. "?.lua" ..
	";" .. GetScriptDirectory() .. "?.lua";

--���Ľű�֧��
__g_chinese_script_support__ = {
	{ "���", "if" },
	{ "��ô", "then" },
	{ "����", "end" },
	{ "����", "else" },
	{ "�������", "elseif" },
	{ "ѭ��", "while" },
	{ "�ֲ�����", "local" },
	{ "����", "return" },
	{ "��", "nil" },
	{ "��", "true" },
	{ "��", "false" },
	{ "��", "not" },
	{ "û��", "not" },
	{ "ִ��", "do" },
	{ "��", "and" },
	{ "��", "or" },
	{ "ת�����ַ���", "tostring" },
	{ "���庯��", "function" },
	{ "�ظ�", "repeat" },
	{ "ֱ��", "until" },
};

--return true
function RetTrue()
	return true;
end

g_tbl_make_match_substr_ = {};
g_tbl_make_match_substr_.__add = function( lhs, rhs )
	if type(rhs) ~= "string" then
		LuaLogE("�����������ַ�������");
		assert(false, "����ƥ�����ַ����Ĳ����������ַ�������");
		return;
	end
	lhs.str_ = lhs.str_ .. WideCharToGbk(UnsensePerlMetachar(GbkToWideChar(rhs))) .. ".*";
	return lhs;
end

--����ƥ�����ַ���
function MakeMatchSubStr( str_head )
	if type(str_head) ~= "string" then
		LuaLogE("�����������ַ�������");
		assert(false, "����ƥ�����ַ����Ĳ����������ַ�������");
		return;
	end
	local tbl_tmp = {};
	tbl_tmp.str_ = ".*" .. WideCharToGbk(UnsensePerlMetachar(GbkToWideChar(str_head))) .. ".*";
	setmetatable(tbl_tmp, g_tbl_make_match_substr_);
	return tbl_tmp;
end

--load all lua files for initial
LoadAndReloadLuaFiles(GLuac_Instance());


