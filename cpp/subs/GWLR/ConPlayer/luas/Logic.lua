--��½����������
g_login_service_pos = {
	--ser x����, ser y���꣬������ID, ser region x, ser region y
	ɽ������ = { 633, 420, 257, 452, 367 },
	����ɭ�� = { 603, 462, 513, 452, 367 },
	�������� = { 575, 502, 769, 452, 367 },
	��ɫ�糡 = { 537, 541, 1025, 452, 367 },
	����Ӫկ = { 511, 585, 1281, 452, 367 },
	�������� = { 482, 630, 1537, 452, 367 },
	�ն�֮�� = { 451, 667, 1793, 452, 367 },
	����Ͽ�� = { 482, 699, 2049, 452, 367 },
	����Ͽ�� = { 650, 595, 2305, 452, 367 },

	������ɽ = { 633, 420, 258, 405, 419 },
	ħ��ʥ�� = { 603, 462, 514, 405, 419 },
	����Ͽ�� = { 575, 502, 770, 405, 419 },
	����ɽ�� = { 537, 541, 1026, 405, 419 },
	�籩Ͽ�� = { 511, 585, 1282, 405, 419 },
	���º��� = { 482, 630, 1538, 405, 419 },
	³���㳡 = { 451, 667, 1794, 405, 419 },

	�ҽ����� = { 633, 420, 259, 361, 478 },
	���ؼ�̳ = { 603, 462, 515, 361, 478 },
	������϶ = { 575, 502, 771, 361, 478 },
	���ɺ��� = { 537, 541, 1027, 361, 478 },

	�ƽ���ͷ = { 633, 420, 260, 313, 534 },
	��˪���� = { 603, 462, 516, 313, 534 },
	ɳĮ֮�� = { 575, 502, 722, 313, 534 },
	����ս�� = { 537, 541, 1028, 313, 534 },
	ħŮլۡ = { 511, 585, 1284, 313, 534 },
	�����̳ = { 482, 630, 1540, 313, 534 },
	���˷Ͽ� = { 451, 667, 1796, 313, 534 },
	ħ����ַ = { 482, 699, 2052, 313, 534 },
};
function Login_GetSerRegionPosX( service_name )
	return g_login_service_pos[service_name][4];
end
function Login_GetSerRegionPosY( service_name )
	return g_login_service_pos[service_name][5];
end
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
