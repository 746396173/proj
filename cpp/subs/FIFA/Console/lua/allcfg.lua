--��½����������
g_login_service_pos = {
	--x���꣬y���꣬������ID
	�������� = { 626, 359, 16777473 },
	���ϵ��� = { 833, 353, 33554689 },
	������ͨ = { 1001, 354, 16777985 },
	���ϵ��� = { 1001, 354, 50331905 },
};
function Login_GetServicePosX( service_name )
	return g_login_service_pos[service_name][1];
end
function Login_GetServicePosY( service_name )
	return g_login_service_pos[service_name][2];
end
function Login_GetServiceNames( vec )
	for k, _ in pairs(g_login_service_pos) do
		vec:PushBack(k);
	end
end
--�õ�������ID
function Login_GetServiceId( service_name )
	return g_login_service_pos[service_name][3];
end

function MixLua()
	JsonValue = 1;
end
