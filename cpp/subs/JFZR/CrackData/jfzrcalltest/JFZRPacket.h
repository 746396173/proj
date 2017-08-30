/////////////////////////////////////////////////////////////////////////////////////////
// ����֮����Ŀ֮������������
// ˵�������еĺͷ���йصĺ����ӿھ��ṩ�ڴ�
// by reversal
/////////////////////////////////////////////////////////////////////////////////////////


#define JFZR_REVERSAL_PACKET_SEND_HEADER				0x55e0


/////////////////////////////////////////////////////////////////////////////////////////
// �������ܽӿڲ���
WORD GetHash(const wchar_t* wszStr);
DWORD GetHash(const wchar_t* pszStr1, const wchar_t* pszStr2);
DWORD GetSigHash(const wchar_t* pszStr);
DWORD WINAPI JFZR_GetTickCount();
DWORD WINAPI JFZR_AllmMemory_Alloc(int nsize);
void WINAPI JFZR_AllmMemory_Free(DWORD dwAllocAddr);
const wchar_t* GetChinese(const wchar_t* ptheEnglish);
DWORD GetProjectileSerial();
DWORD GetSkillObjAddr(DWORD ptheSkillObjAddr,DWORD* dwPoint);
DWORD LockAdd(DWORD dwLockAddr);
void UserSkillLockAdd();
FLOAT GetSpeed(DWORD dwSpeedAddr);
WORD GetDirection(FLOAT fDirection);
void JFZR_GameMemcpy(DWORD lpAddr, WCHAR* pszStr);
/////////////////////////////////////////////////////////////////////////////////////////
// ����ӿڲ���
int WINAPI JFZR_UserSkillPacket1(
						OUT char* pOutszSendBuffer,
						DWORD dwSkillId
						);

int WINAPI JFZR_UserSkillPacket2( 
						OUT char* pOutszSendBuffer, 
						const wchar_t* pszJobName , 
						const wchar_t* pszSkillName, 
						float x, 
						float y, 
						float z, 
						DWORD dwDirectionX,
						DWORD dwDirectionY,
						FLOAT	fClientAbsoluteTime,
						DWORD	dwSkillId,
						DWORD dwSkillLevel,
						DWORD dwPrevActionPlayTime
						);

int WINAPI JFZR_UserSkillPacket3(
						OUT char* pOutszSendBuffer,
						const wchar_t* pszJobName,
						float x,
						float y,
						float z,
						DWORD dwDirectionX,
						DWORD dwDirectionY,
						FLOAT	fClientAbsoluteTime,
						DWORD dwPrevActionPlayTime
						);

int WINAPI JFZR_SkillHitPacketHeader(
									 OUT char* pOutszSendBuffer,
									 int nsize);

int WINAPI JFZR_SkillHitPacketBody(
								   OUT char* pOutszSendBuffer,
								   int nitem,					// �����������������,��0��ʼ���൱�ڽṹ��������±�
								   DWORD dwProjectileSerial,	// ������ţ����Ը�0��Ч
								   DWORD dwDefenderSerial,		// ���������
								   DWORD dwAttackerSerial,		// ���������
								   FLOAT fAttackPowerRate,		// ����ǰ���ٶ�
								   DWORD dwProjectileHash,		// ��������hash������Щ���ܲ�һ�������弼�����ݿ��ṩ����
								   DWORD dwActionHash,			// �ж�hash
								   DWORD dwSkillHash,			// ����hash
								   DWORD dwSkillLevel,			// ���ܵȼ�
								   DWORD dwTimeStamp,			// ʱ��������Ը�0��Ч
								   BYTE  bFirstHit,
								   BYTE  bIsCounterAttack,
								   WORD  wPhysicalAttribute,
								   wchar_t* pwszElementalAttribute,		// ����Ԫ������
								   DWORD	dwDeltaHp
								   );

int WINAPI JFZR_StartStage(
								   OUT char* pOutszSendBuffer,
								   const wchar_t* pszStartStageName,
								   const wchar_t* pszWarpGateId,
								   int nStageLevel,
								   BYTE	bIsRestart);

int WINAPI JFZR_GotoNextRoom1(
							 OUT char* pOutszSendBuffer,
							 const wchar_t* pszRoleName,		// �������
							 const wchar_t* pszWarp				// �ڼ�����
							 );


int WINAPI JFZR_GotoNextRoom2(
							  OUT char* pOutszSendBuffer,
							  DWORD dwRoleSerial,
							  float x,
							  float y,
							  float z,
							  DWORD dwDirectionX,
							  DWORD dwDirectionY
							  );

int WINAPI JFZR_ChangeSector(
							 OUT char*			pOutszSendBuffer,
							 const wchar_t*	pszWarp,		// �ڼ�����
							 DWORD				dwValidationData_Y,
							 DWORD				dwValidationData_X,
							 BYTE				bIsDummyExist,
							 FLOAT				fAttackSpeed,
							 FLOAT				fMoveSpeed,
							 FLOAT				fEvadeRating
							  );

int WINAPI JFZR_RetCity(
						OUT char* pOutszSendBuffer
						);

int WINAPI JFZR_PickUpItem1(
						   OUT char* pOutszSendBuffer,
						   DWORD dwItemSerial		// ��Ʒ���
						   );

int WINAPI JFZR_PickUpItem2(
							OUT char* pOutszSendBuffer,
							DWORD dwFlag
							);

int WINAPI JFZR_RepairItem(  OUT char* pOutszSendBuffer );

int WINAPI JFZR_ActionSyncPacket(
					 OUT char*	pOutszSendBuffer,
					 DWORD		dwRoleSerial,			// �������
					 DWORD		dwActionHash,
					 float		fx,						// ����
					 float		fy,
					 float		fz,
					 float		fDirectionX,			// ����1
					 float		fDirectionY,
					 float		fDirectionZ,
					 DWORD		dwDirectionX,			// ����2
					 DWORD		dwDirectionY,
					 BYTE		bSkipValidation,
					 float		fPrevActionPlayTime,
					 DWORD		dwActionSerial,
					 DWORD		dwPrevActionSerial,
					 DWORD		dwRandomSeed,
					 FLOAT		fClientAbsoluteTime,
					 BYTE		bbExistParams
					 );

int WINAPI JFZR_VillageActionSyncPacket(
										OUT char*	pOutszSendBuffer,
										DWORD		dwRoleSerial,			// �������
										const wchar_t*	pszJobName,			// ��ɫְҵ
										const wchar_t*	pszCmdName,			// "FastRun" �� "Stand"
										float		fx,						// ����
										float		fy,
										float		fz,
										float		fDirectionX,			// ����1
										float		fDirectionY,
										float		fDirectionZ,
										DWORD		dwDirectionX,			// ����2
										DWORD		dwDirectionY
										);

int WINAPI JFZR_EquipItem(
						  OUT char*	pOutszSendBuffer,
						  int nEquipSlot,					// װ����
						  int nInvenSlot,					// Ҫ����������Ʒ������
						  const wchar_t* pwszEquipTab,		// L"BASIC"
						  const wchar_t* pwszInvenTab		// L"EQUIPMENT_TAB"
						  );

int WINAPI JFZR_UnEquipItem(
							OUT char*	pOutszSendBuffer,
							int nEquipSlot,					// װ����
							int nInvenSlot,					// û����Ʒ�ı�����
							const wchar_t* pwszEquipTab,	// L"BASIC"
							const wchar_t* pwszInvenTab		// L"EQUIPMENT_TAB"
							);
int WINAPI JFZR_UseForItem(
						   OUT char*	pOutszSendBuffer,
						   int nUsingSlotIndex,					// ���������ʯλ��
						   int nTargetSlotIndex					// װ��λ��
						   );

int WINAPI JFZR_BuyItem(
						OUT char*	pOutszSendBuffer,
						const wchar_t*		pwszNpcName,// NPC����
						DWORD		dwSellId,			// ��ƷID
						int			nCount				// ��Ʒ����
						);

int WINAPI JFZR_SellItem(
						 OUT char*	pOutszSendBuffer,
						 const wchar_t*	pwszNpcName,		// NPC����
						 int			nTabCategory,		// 0,��ʾ��ͨ��; 1,��ʾ����Ʒ��;2,��ʾ������;3,��ʾ������
						 int			nSlotIndex,			// �������󱳰����ڼ���
						 int			nCount				// ��Ʒ����
						 );

int WINAPI JFZR_ChangeVillage(
							  OUT char*	pOutszSendBuffer,
							  const wchar_t*	pwszVillageId			// ��ׯ��id
							  );
int WINAPI JFZR_LearnSkill(
						   OUT char*		pOutszSendBuffer,
						   const wchar_t*	pwszSkillName,			// ��������
						   DWORD			dwSkillLevel			// ������ļ��ܵȼ�
							  );

int WINAPI JFZR_CreatePlayer(
							 OUT char*	pOutszSendBuffer,
							 const wchar_t*	pszRoleName,		// ������ɫ������
							 DWORD dwPlayerGender,				// ��ɫ�Ա�Ĭ�ϵ�һ������0���˲���һֱĬ��Ϊ0
							 DWORD dwClassType					// ְҵ���� // 1.����ʿ  2.������  9.��ħʦ
							 );

int WINAPI JFZR_SelectPlayer(
							 OUT char*		pOutszSendBuffer,
							 const wchar_t*	pszRoleName				// ��ɫ����
							 );

int WINAPI JFZR_DeselectPlayer(
							   OUT char*		pOutszSendBuffer
							   );
int WINAPI JFZR_ListPlayers(
							OUT char*		pOutszSendBuffer
							);

int WINAPI JFZR_RequestSwitchChannel(
									 OUT char*		pOutszSendBuffer,
									 const wchar_t*	pszChannelName				// Ƶ������
									 );


int WINAPI JFZR_SwitchChannel(
							  OUT char*		pOutszSendBuffer,
							  const wchar_t*	pszChannelName,				// Ƶ������
							  const wchar_t*	pszAccountId,				// QQ�˺�
							  const wchar_t*	pszSessionKey				// KEY
							  );

int WINAPI JFZR_MailSendHeader(
							   OUT char*			pOutszSendBuffer,
							   const wchar_t*		pszTitle,				// �ʼ�����
							   const wchar_t*		pszReceiverId,			// �������
							   const wchar_t*		pszMessage,				// �ʼ�����
							   UINT64				nGold,					// �ʼ����
							   int					nsize,					// �ʼ���Ʒ����
							   LONGLONG				llOidReceiver
									 );

int WINAPI JFZR_MailSendBody(
							 OUT char*			pOutszSendBuffer,
							 int					nitem,				// ��n����Ʒ
							 wchar_t*				pwszInventoryTab,	// װ��:"EQUIPMENT_TAB" ����:"MATERIAL_TAB"
							 int					nItemSlotIndex,		// ��Ʒ���ڱ�����
							 int					nCount				// ��Ʒ����
							 );

// �������ܣ������ʼ�β��
int WINAPI JFZR_MailSendTail(
							 OUT char*			pOutszSendBuffer
							 );

int WINAPI JFZR_GetAttachments(
							   OUT char*			pOutszSendBuffer,
							   LONGLONG		llMailSerial,
							   BYTE			bIsFirst
							   );

int WINAPI JFZR_MailRemove(
						   OUT char*			pOutszSendBuffer,
						   LONGLONG		llMailSerial,
						   BYTE			bIsFirst
						   );

int WINAPI JFZR_JoinVillage(
							OUT char*			pOutszSendBuffer
							);

// �������ܣ���������
int WINAPI JFZR_Accept(
					   OUT		char*		pOutszSendBuffer,
					   const	wchar_t*	pszQuestId,					// ����id
					   DWORD				dwRewardItemId,				// 1
					   DWORD				dwInventoryTabIndex,		// -1
					   DWORD				dwInventorySlotIndex		// -1
					   );

// �������ܣ��������
int WINAPI JFZR_Complete(
						 OUT		char*		pOutszSendBuffer,
						 const	wchar_t*	pszQuestId,					// ����id
						 const	wchar_t*	pszRewardItemId
						 );

int WINAPI JFZR_GiveUp(
					   OUT		char*		pOutszSendBuffer,
					   const		wchar_t*	pszQuestId					// ����id
					   );

int WINAPI JFZR_TeleportToVillage(
								  OUT		char*		pOutszSendBuffer,
								  const		wchar_t*	pwszQuestId,
								  DWORD		dwState
								  );

int WINAPI JFZR_Disassembly(
							  OUT		char*		pOutszSendBuffer,
							  DWORD		dwTabCategory,
							  DWORD		dwSlotIndex,
							  WORD		wIsAvatarItem
							  );

int WINAPI JFZR_StageReward(
							OUT		char*		pOutszSendBuffer,
							DWORD	dwRewardIndex
							);

int WINAPI JFZR_RequestProductList(
								   OUT		char*		pOutszSendBuffer,
								   wchar_t*	pwszCategory,
								   wchar_t*	pwszKeyWord,
								   DWORD		dwPageNum
								   );

int WINAPI JFZR_BuyProduct(
						   OUT		char*		pOutszSendBuffer,
						   LONGLONG		llOidMarket,
						   DWORD		dwCount
						   );

int WINAPI JFZR_RegisterProduct(
								OUT		char*		pOutszSendBuffer,
								wchar_t*	pwszName,
								DWORD		dwItemTabCategory,
								DWORD		dwItemSlotIndex,
								LONGLONG	llPrice,
								DWORD		dwPeriod,
								DWORD		dwCount
								);

int WINAPI JFZR_RequestMyProductList(
									 OUT		char*		pOutszSendBuffer
									 );

int WINAPI JFZR_UnregisterProduct(
								  OUT		char*		pOutszSendBuffer,
								  LONGLONG	llOidMarket
									 );

int WINAPI JFZR_Activity(
						 OUT		char*		pOutszSendBuffer,
						 DWORD		dwType,
						 DWORD		dwCount,
						 DWORD		dwDefenderSerial,
						 DWORD		dwdwAttackerSerial
						 );


int WINAPI JFZR_Test(
					 OUT		char*		pOutszSendBuffer,
					 DWORD	dwIndex
					 );

int WINAPI JFZR_RequestProductInfo(
								   OUT		char*		pOutszSendBuffer,
								   DWORD		dwItemTabCategory,
								   DWORD		dwItemSlotIndex
								   );

int WINAPI JFZR_OpenItemPackage(
								OUT		char*		pOutszSendBuffer,
								int			nItemPackageTabIndex,	// ��Ʒ��
								WORD		wItemPackageSlotIndex,	// ��Ʒ�ڵڼ���
								int			nRequireItemTabIndex,	// ��ϴ���Ʒ��Ҫ����Ʒ  -1��ʾû��
								WORD		wRequireItemSlotIndex	// ��Ʒ�ڵڼ��������������Ʒ������0
								);
int WINAPI JFZR_UseItem(
						OUT		char*		pOutszSendBuffer,
						int			nTabIndex,	// ��Ʒ��
						WORD		wSlotIndex	// ��Ʒ�ڵڼ���
						);

int WINAPI JFZR_CreateNpcByClient(
								  OUT		char*			pOutszSendBuffer,
								  DWORD			dwMasterSerial,
								  DWORD			dwRequestSerial
								  );

int WINAPI JFZR_DestroyActors(
							  OUT		char*		pOutszSendBuffer,
							  DWORD		dwSerial
							  );