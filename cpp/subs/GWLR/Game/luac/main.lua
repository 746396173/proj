--dofile==ÿ�ζ�Ҫ���롣loadfile==ֻ����(����)�ļ�һ��
--require�����μ���ͬһ���ļ���

__g_lua_files__ = {
	"Test", "Logic", "task", "BodyPartInfo", "MaterialMap", "TotalStagePosInfo",
	"Scri_Commands"
};

--set lua path
package.path = GetLuaDirectory() .. "?.lua" ..
	";" .. GetScriptDirectory() .. "?.lua";

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
	{ "û", "not" },
	{ "ִ��", "do" },
	{ "��", "and" },
	{ "��", "or" },
	{ "ת�����ַ���", "tostring" },
	{ "���庯��", "function" },
	{ "�ظ�", "repeat" },
	{ "ֱ��", "until" },
	{ "�ж�", "break" }
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

--���ؽű��ļ�
function ���ؽű��ļ�( file_name )
	SetCurRunScriptNameLevel0(file_name)
	RunInfo("���ؽű��ļ�:" .. file_name)
	return LoadScriptFile(file_name);
end

function �������ýű��ļ�( file_name )
	RunInfo("�������ýű��ļ�:" .. file_name)
	return LoadScriptFile("����\\" .. file_name);
end

function �պ���()
end

function ��������Ŀ¼�ű�( �ű��� )
	return LoadScriptFile("����\\" .. �ű���);
end

function RetBoolDef( res, def )
	if type(res) ~= "boolean" then
		return def
	end
	return res
end
---------------------------------------
--load all lua files for initial
LoadAndReloadLuaFiles(GLuac_Instance());

g_str_MakeMatchSubStrmb = "ad3738d3-6c45-5077-b5e5-809dd30a4c52"
g_str_MakeMatchSubStrxe = "09fbf906-9ba4-5fd7-82cc-f48609ebb29e"
g_str_MakeMatchSubStrpmb = "d972ebbf-aac4-56fc-8879-dcfec2c3d46b"
