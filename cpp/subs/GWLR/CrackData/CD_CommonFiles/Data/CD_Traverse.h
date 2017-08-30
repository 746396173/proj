#pragma once
/*
@author zhp
@date 2016/4/11 21:40
*/
#include "CD_Structs.h"


class CD_Traverse{
public:
	typedef std::function<bool(stCD_NetObj*)> DoNetObjFuncT;
	typedef std::function<bool(stCD_Node*)> DoNodeFuncT;
	typedef std::function<bool(stCD_Item*, int idx)> DoItemFuncT;
	typedef std::function<bool(stCD_ItemDb*)> DoItemDbFuncT;
	typedef std::function<bool(stCD_TaskDb*)> DoTaskDbFuncT;
	typedef std::function<bool(stCD_MapDb*)> DoMapDbFuncT;
	typedef std::function<bool(stCD_FarmDb*)> DoFarmDbFuncT;
	typedef std::function<bool(stCD_ShopDb*)> DoShopDbFuncT;
	typedef std::function<bool(stCD_SeedDb*)> DoSeedDbFuncT;
	typedef std::function<bool(stCD_CraftDb*)> DoCraftDbFuncT;
	typedef	std::function<bool(stCD_MenufactureDb*)> DoMenufactureDbFuncT;
	typedef std::function<bool(stCD_GridItemInfo*)> DoGridItemInfoT;
	typedef std::function<bool(stCD_BuffDb*)> DoBuffDbT;
	typedef std::function<bool(stCD_ObjBase*)> DoLocalObjT;
	typedef	std::function<bool(stCD_ShangJinInfo*)> DoShangJinInfoT;
	typedef	std::function<bool(stCD_KingQuestInfo* king_info)> DoKingQuestInfoT;
	typedef std::function<bool(stCD_UiCtrl*)> DoUiCtrlT;
	typedef std::function<bool(stCD_UiMng*)> DoUiMngT;

private:
	struct TraverseExcept : std::exception{
		TraverseExcept(const char* str) : std::exception(str){}
	};

public:
	//ͨ��packet_id��֯���������ݽṹ��һ��ֻ�ܱ�����NPC
	static int TraverseNetObjs(const DoNetObjFuncT& func);
	//ͨ��id(local id)��֯���������ݽṹ���ɱ��������б��ض���
	static int TraverseLocalObjs(const DoNodeFuncT& func);
	//������Ʒ
	static int TraverseItems(const stCD_GridsMgr& grids_mgr, const DoItemFuncT& func);
	//������Ʒģ��
	static int TraverseItemDb(const DoItemDbFuncT& func);
	//��������ģ��
	static int TraverseMapDb(const DoMapDbFuncT& func);
	//��������ģ��
	static int TraverseTasksDb(const DoTaskDbFuncT& func);
	//�����ѽ�����
	static int TraverseReceivedTask(const DoNodeFuncT& func);
	//����farm db
	static int TraverseFarmDb(const DoFarmDbFuncT& func);
	//������Ʒģ��
	static int TraverseShopDb(const DoShopDbFuncT& func);
	//��������ģ��
	static int TraverseSeedDb(const DoSeedDbFuncT& func);
	//��������ģ��
	static int TraverseCraftDb(const DoCraftDbFuncT& func);
	//��������ģ��
	static int TraverseMenufactureDb(const DoMenufactureDbFuncT& func);
	//�������
	static int TraverseGiftInfo(const DoNodeFuncT& func);
	//����������
	static int TraverseSupplyBox(const DoGridItemInfoT& func);
	//�����ʼ�
	static int TraverseMails(const DoNodeFuncT& func);
	//����buff db
	static int TraverseBuffDb(const DoBuffDbT& func);
	//������ǰbuff
	static int TraverseCurBuff(const DoNodeFuncT& func);
	//�������б��ض���
	static int TraverseAllLocalObjs(const DoLocalObjT& func);
	//������ǰ�ͽ���Ϣ
	static int TraverseCurShangJinInfo(const DoShangJinInfoT& func);
	//������������
	static int TraverseKingQuestInfo(const DoKingQuestInfoT& func);
	//����UI�ؼ�
	static int TraverseUiCtrls(const DoUiCtrlT& func);
	//����ui mng
	static int TraverseUiMng(const DoUiMngT& func);

public:
	static void DebugInfo_NetObjs();
	static void DebugInfo_LocalObjs();
	static void DebugInfo_CurRoleInfo();
	static void DebugInfo_CurMapInfo();
	static void DebugInfo_AllPackagesMgr();
	static void DebugInfo_TheItemDb(int item_id_min, int item_id_max);
	static void DebugInfo_TheTaskDb(int task_id_min, int task_id_max);
	static void DebugInfo_TheMapDb(int map_id_min, int map_id_max);
	static void DebugInfo_ReceivedTask();
	static void DebugInfo_AccetableTask();
	static void DebugInfo_ChapterInfo();
	static void DebugInfo_EnterableFbInfo();
	static void DebugInfo_TheFarmDb(int farm_db_id_min, int farm_db_id_max);
	static void DebugInfo_CurFarmFacility();
	static void DebugInfo_TheShopDb(int min, int max);
	static void DebugInfo_TheSeedDb(int min, int max);
	static void DebugInfo_TheCraftDb(int min, int max);
	static void DebugInfo_TheMenufactureDb(int min, int max);
	static void DebugInfo_GiftInfo();
	static void DebugInfo_SupplyBox();
	static void DebugInfo_Mails();
	static void DebugInfo_TheBuffDb(int min, int max);
	static void DebugInfo_CurBuff();
	static void DebugInfo_AllLocalObjs();
	static void DebugInfo_TheLocalObjs(CD_En_LocalObjType types[], int cnt);
	static void DebugInfo_CurShangJinInfo();
	static void DebugInfo_KingQuestInfo();
	static void DebugInfo_CurUiCtrlInfo();
	static void DebugInfo_UiMng();

	//����
public:
	static void TraTest(int a);

public:
	static int NodeTraverse(stCD_Node* sub_tree_root, const DoNodeFuncT& func);

private:
	static int NodeRecurseTraverse(stCD_Node* sub_tree_root, stCD_Node* null_node, const DoNodeFuncT& func);
	static int TraverseItemDbImpl(int item_id_min, int item_id_max, const DoItemDbFuncT& func);
	static int TraverseTaskDbImpl(int task_id_min, int task_id_max, const DoTaskDbFuncT& func);
	static int TraverseMapDbImpl(int map_id_min, int map_id_max, const DoMapDbFuncT& func);
	static int TraverseFarmDbImpl(int farm_db_id_min, int farm_db_id_max, const DoFarmDbFuncT& func);
	static int TraverseShopDbImpl(CD_En_ShopInfoCategory cate_min, CD_En_ShopInfoCategory cate_max, const DoShopDbFuncT& func);
	static int TraverseSeedDbImpl(int item_id_min, int item_id_max, const DoSeedDbFuncT& func);
	static int TraverseCraftDbImpl(int craft_id_min, int craft_id_max, const DoCraftDbFuncT& func);
	static int TraverseMenufactureDbImpl(int id_min, int id_max, const DoMenufactureDbFuncT& func);
	static int TraverseBuffDbImpl(int id_min, int id_max, const DoBuffDbT& func);
	static void DebugInfoTheObj(stCD_ObjBase* obj);
};