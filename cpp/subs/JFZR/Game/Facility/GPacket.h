#pragma once
/*
@author zhp
@date 2014/7/1 20:44
@purpose for packet
*/
#include <Common/GameObjBase.h>
#include "GItem.h"

class GPacket : public GGameObjMgrBase{
public:
	GPacket();

	//���ÿ����Ʒ��
public:
	GItemMgr_Normal& GetTabNormal();
	GItemMgr_Consume& GetTabConsume();
	GItemMgr& GetTabTask();
	GItemMgr& GetTabMaterial();
	GItemMgr& GetTabAvatar();
	GItemMgr& GetTabEquiped();
	GItemMgr& GetTabAvatarEquiped();
	GItemMgr* FindByTabCategory( GType::enTabCategory tab_category );

	//�����빹��
public:
	bool UpdateAll();
	bool RebuildUpdateAll();
	bool UpdateNormal();
	bool RebuildUpdateNormal();
	bool UpdateConsume();
	bool RebuildUpdateConsume();
	bool UpdateTask();
	bool RebuildUpdateTask();
	bool UpdateMaterial();
	bool RebuildUpdateMaterial();
	bool UpdateAvatar();
	bool RebuildUpdateAvatar();
	bool UpdateEquiped();
	bool RebuildUpdateEquiped();
	bool UpdateAvatarEquiped();
	bool RebuildUpdateAvatarEquiped();

	//����
public:
	//�Զ�����װ��
	bool AutoReplaceEquip();

private:
	GItemMgr_Normal	tab_normal_;			//��ͨ
	GItemMgr_Consume tab_consume_;			//����Ʒ
	GItemMgr		tab_task_;				//����
	GItemMgr		tab_material_;			//����
	GItemMgr		tab_avatar_;			//ʱװ1,2,3�������
	GItemMgr		tab_equiped_;			//װ��
	GItemMgr		tab_avatar_equiped_;	//ʱװ�������
};