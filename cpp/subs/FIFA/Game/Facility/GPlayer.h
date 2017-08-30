#pragma once
/*
@author zhp
@date 2014-3-10 14:59
@purpose for game player info
*/
#include <boost/asio.hpp>
#include "json/value.h"
#include "Common/Iterator.h"
#include <boost/shared_ptr.hpp>
#include <boost/function.hpp>
#include <list>
#include "Facility/GTypes.h"
#include "Net/IoTimer.h"
#include <Poco/DateTimeFormat.h>
#include <Poco/DateTimeParser.h>
#include <Poco/DateTimeFormatter.h>
#include <set>
#include <Common/UsefulClass.h>
#include <boost/optional.hpp>
#include <Net/PocoMore.h>

//global functions
//Check result
bool CheckResFromRespond( const Json::Value& respond_msg );

class GPlayer : public Singleton<GPlayer, Singleton_Me>{
	GPlayer();

	//type definition
public:
	//level info
	struct stLevelInfo{
		stLevelInfo();
		stLevelInfo( int level, int exp, int to );
		//get level
		int GetLevel() const;
		//set level
		void SetLevel( int level );
		//get exp
		int GetExp() const;
		//set exp
		void SetExp( int exp );
		//get to
		double GetTo() const;
		//set to
		void SetTo( double to );
		bool ParseFromJsonObj( const Json::Value& json_level_info );

	private:
		int					level_;					//�ȼ�
		int					exp_;					//����
		double				to_;					//�������辭��
	};

	//��Ա
	struct stPlayer{
		stPlayer(){
			grade_ = 0;
			price_ = 0;
			life_ = 0;
			player_pos_ = GType::enPlayerPosition_No;
			spid_ = 0;
		}
		typedef std::list<stPlayer> PlayerContT;

		//ְλ��Ϣ
		struct PositionInfo{
			PositionInfo(){
				pos_ = 0;
			}

			bool ParseFromJsonObj( const Json::Value& pos_info );

			int						pos_;
			Json::Value				starting_;

			static const int		kSecondPos = 28;			//�油ְλ
		};

		const char* GetId() const;
		void SetId( int id );
		int GetGrade() const;
		void SetGrade( int grade );
		double GetPrice() const;
		void SetPrice( double price );
		int GetLife() const;
		void SetLife( int life );
		GType::enPlayerPosition GetPosition() const;
		void SetPosition( GType::enPlayerPosition pos );
		//�õ����ݿ�����ID
		int GetSpid() const;
		//�õ�����ֵ
		int GetAbility() const;
		//�õ���Ա��
		const std::string GetPlayerName() const;
		//�Ƿ���Խ���
		bool CanExchangePlayer() const;
		//������Ա
		void ExchangePlayer( const stPlayer& other );
		//ǿ����Ա
		void EnhancePlayer(const stPlayer& other);
		static bool ExchangePlayers( const PlayerContT& players );
		//parse from json obj
		bool ParseFromJsonObj( const Json::Value& player_obj );
		//�Ƿ���Խ���ְλ
		bool CanExchangePosition( const stPlayer& other );
		//����ְλ
		bool ExchangePostion( stPlayer& other, bool is_send );
		bool ExchangePostionSync( stPlayer& other, bool is_send );
		//�Ƿ���ԴӺ��Ϊ��
		bool CanDegradeFromThirdToNo() const;
		//�Ӻ��Ϊ��
		bool DegradeFromThirdToNo();
		//�Ƿ���Դ�������Ϊ�
		bool CanUpgradeFromNoToThird() const;
		//��������Ϊ�
		bool UpgradeFromNoToThird();
		//�Ƿ���һ����Ա
		bool IsFirstTeamPlayer() const;
		//�Ƿ��Ƕ�����Ա
		bool IsSecondTeamPlayer() const;
		//����������ĸ���
		void MatchEndUpdate( const stPlayer& new_player );
		//�Ƿ���Խ��
		bool CanBeFired() const;
		//���ͽ����Ϣ
		bool SendFireMsg() const;
		//������Ա
		bool SaleSelfAs( double price );
		//�����ʣ�ೡ��
		bool CanBeSale_NoStrict() const;
		bool SaleSelfAs_NoStrict( double price, bool notify_gplayer, bool notify_coor );
		//�Ƿ���Ա�����
		bool CanBeSale() const;
		//�����۸�
		static double AdjustPrice( double price );
		//�Ƿ���������ְλ֮һ
		bool IsInPos( GType::enPlayerPosition player_position[], int position_cnt ) const;

	public:
		//��Ч����ֵ
		static const int			kInvalidAbility = -1;

		std::string					id_;
		int							grade_;			//ǿ���ȼ�
		double						price_;			//��Ա��ֵ
		int							life_;			//ʣ�ೡ��
		GType::enPlayerPosition		player_pos_;	//��Աְλ
		PositionInfo				position_info_;	//ְλ��Ϣ
		int							spid_;			//���ݿ�����ID
	};

	//��Ʒ
	struct stItem{
		struct stUseHelper;
		typedef bool (*UseMsgParamT) ( Json::Value& msg, const stUseHelper& use_hlp );
		struct stUseHelper{
			int						item_id_;
			stItem::UseMsgParamT	msg_param_handler_;
			bool					is_encrypt_;
		};

		stItem(){
			itemid_ = 0;
			remains_ = 0;
			expired_ = true;
		}

		//ʹ��
		bool Use();
		bool UseEx( const stUseHelper& use_hlp );
		bool SmartUse();
		//can be use?
		bool CanUse() const;

		const char* GetId() const;
		void SetId( const char* id );
		int GetItemId() const;
		void SetItemId( int item_id );
		int GetRemains() const;
		void SetRemains( int remains );
		bool GetExpired() const;
		void SetExpired( bool expired );
		//parse from json obj
		bool ParseFromJsonObj( const Json::Value& item_obj );

		//��ɫ�ʺſ�
		static int ItemId_BlueCard();
		//��ɫ�ʺſ�
		static int ItemId_GreenCard();
		//��ɫ�ʺſ�
		static int ItemId_RedCard();
		//��ɫ�ʺſ�
		static int ItemId_PurpleCard();
		//����EP��
		static int ItemId_EpCard();
		//�µ�����EP��
		static int ItemId_EpCardNew();
		//��Ա������
		static int ItemId_ChangeCard();
		//�Զ�����ȯ
		static int ItemId_AutoMatchTicket();
		//��ɫ��̽��
		static int ItemId_BlueBallCard();
		//��ɫ��̽��
		static int ItemId_GreenBallCard();
		//��ɫ��̽��
		static int ItemId_RedBallCard();
		//13ǰ����Ա��
		static int ItemId_13ForwardCard();
		//13�г���Ա��
		static int ItemId_13MidCard();
		//13������Ա��
		static int ItemId_13BackCard();
		//13�Ž���Ա��
		static int ItemId_13GateCard();
		//���籭32ǿ���Ҷ���Ա��
		static int ItemId_32CountryCard();
		//��ɫ��̽��
		static int ItemId_OrangeCard();
		//w��
		static int ItemId_WCard();

		//use helper function
	public:
		//ָ����Ա��
		static bool OpenTheSpecificCard100( Json::Value& msg, const stUseHelper& use_hlp ); 
		static bool OpenTheSpecificCard200( Json::Value& msg, const stUseHelper& use_hlp ); 
		static std::pair<const stUseHelper*, int> GetSpecificUse();

		std::string					id_;			//id
		int							itemid_;		//��ƷID����ʾ��Ʒ����������	
		int							remains_;		//����
		bool						expired_;		//�Ƿ���
	};

	//�ɾ�
	struct Achievement{
		Achievement();
		//parse from json obj
		bool ParseFromJsonObj( const Json::Value& achievement_item );
		//�Ƿ������ȡ
		bool CanBeCollect() const;
		//��ȡ
		bool Collect();

		std::string					id_;
		int							grade_;
		bool						available_;		//�Ƿ������ȡ�ɾ�
	};

	//���
	struct GiftPackage{
		GiftPackage();
		//parse from json obj
		bool ParseFromJsonObj( const Json::Value& achievement_item );
		//�Ƿ������
		bool CanBuy() const;
		//������
		bool Buy();

		int					shop_id_;
		int					product_id_;
		double				price_;
	};

	//������
	struct stOfferItem{
		//type definitions
		typedef std::list<stOfferItem> ContT;

		stOfferItem(){
			price_ = 0;
			spid_ = 0;
			grade_ = 0;
		}
		bool ParseFromJsonObj( const Json::Value& sold_player );
		bool ConvertToJson( Json::Value& sold_player ) const;
		//friend bool operator < ( const stOfferItem& lhs, const stOfferItem& rhs );
		friend bool operator == ( const stOfferItem& lhs, const stOfferItem& rhs );
		//�������Ա
		bool Buy( bool notify_coor ) const;
		//�Ƿ���Թ���
		bool CanBuy() const;

		std::string			id_;				//������id
		double				price_;				//���ۼ۸�
		int					spid_;
		Poco::DateTime		issued_at_;			//������Ա��ʱ��
		int					grade_;				//ǿ���ȼ�
	};
	//�ҵĳ�����
	struct stSelfOfferItem : public stOfferItem{
		//type definition
		enum enSoldState{
			kSS_Waiting = 0,			//�ȴ�����
			kSS_Sold,					//�Ѿ�����
			kSS_Expired,				//����
			kSS_Invalid,				//��Ч
		};
		typedef std::list<stSelfOfferItem> ContT;

		stSelfOfferItem(){
			sold_state_ = kSS_Invalid;
		}
		bool ParseFromJsonObj( const Json::Value& sold_player );
		bool ConvertToJson( Json::Value& sold_player ) const;
		//ȡ������������Ա
		bool CancelExpired( bool notify_gplayer );
		//���������ɹ�
		bool SoldDone( bool notify_gplayer );
		//����ʱ��̫����
		bool IsWaitSaleTimeTooLong() const;
		//ȡ��������������Ա
		bool CancelSale_Waiting( bool notify_gplayer );

		std::string					player_id_;		//��Աid
		enSoldState					sold_state_;	//����״̬
	};

	//������������Ա����Ϣ
	struct stSellingPlayerInfo{
		//type definitions
		typedef std::multimap<int, stSellingPlayerInfo> ContT;

		stSellingPlayerInfo();
		bool ParseFromJsonObj( const Json::Value& selling_player );
		//�������Ա
		bool Buy() const;
		//�Ƿ���Թ���
		bool CanBuy() const;
				
		std::string				id_;			//������id
		int						cnt_;			//����������
		int						grade_;			//ǿ���ȼ�
		Poco::DateTime			oldest_date_;	//��������ʱ��
		double					price_;			//��Ǯ
		int						spid_;
		double					price_lower_;	//��ͼ�Ǯ
		double					price_upper_;	//��߼�Ǯ
		double					price_default_;	//Ĭ�ϼ�Ǯ
	};
	//��Ա�����������۸�Χ
	struct stSellingPriceRange{
		//type definitions
		typedef std::pair<int, int> KeyT;
		typedef std::map<KeyT, stSellingPriceRange> ContT;

		stSellingPriceRange();
		bool ParseFromJsonObj( const Json::Value& selling_price );
		//�Ƿ���Ҫ����
		bool NeedUpdate() const;
		//����
		bool Update( int spid, int grade );
		//�Ƿ��ڼ۸�Χ��
		bool InRange( double price ) const;
		//get/set
		double GetPriceLower() const;
		void SetPriceLower( double price_lower );
		double GetPriceUpper() const;
		void SetPriceUpper( double price_upper );
		double GetPriceDefault() const;
		void SetPriceDefault( double price_default );

		double				price_lower_;		//��ͼ۸�
		double				price_upper_;		//��߼۸�
		double				price_default_;		//Ĭ�ϼ۸�
		//int					price_lowest_;		//δ֪
		int					reg_fee_;			//�ǼǷ�
		Poco::DateTime		lastest_time_;		//ˢ����Ա�۸��ʱ��
	};

	//plaer iterator
	typedef Iterator<stPlayer*> stPlayerIter;
	typedef boost::shared_ptr<stPlayerIter> SharedPlayerIter;
	typedef stPlayer::PlayerContT PlayerContT;
	typedef std::vector<stItem> ItemContT;
public:
	static GPlayer& GetMe();
	//set ep
	void SetEp( double ep );
	//get ep
	double GetEp() const;
	//get gp
	int GetGp() const;
	//set gp
	void SetGp( int gp );
	//�õ����е���Ա
	PlayerContT& GetAllPlayers();
	//�õ����е���Ʒ
	ItemContT& GetAllItems();
	//set bag items
	bool SetBagItems( const Json::Value& bag_items_array );
	//find item by id
	stItem* FindItemById( const char* id );
	//find item by itemid
	stItem* FindItemByItemId( int item_id );
	//get level info
	const stLevelInfo& GetLevelInfo() const;
	//set level info
	void SetLevelInfo( const stLevelInfo& level_info );
	bool SetJsonLevelInfo( const Json::Value& json_level_info );
	//�õ���������
	const char* GetName() const;
	//���ý�������
	void SetName( const char* name );
	//���ñ�����������
	void SetMatchLimitCnt( int cnt );
	int GetMatchLimitCnt() const;
	//ͨ��ID�õ���Ա
	stPlayer* FindPlayerById( const char* id ) const;
	//ͨ��json��������һ����Ա
	bool AddPlayerFromJsonObj( const Json::Value& player_obj, PlayerContT& out_players_cont );
	//�������е���Ա
	bool Init_SetAllPlayers( const Json::Value& players_array );
	//���������������Ա
	bool MatchEnd_UpdatePlayers( const Json::Value& players_obj );
	//�Ƿ���Խ�����Ա
	bool IsCanExchangePlayer() const;
	//�������Խ�������Ա�ĵ�����
	SharedPlayerIter CreateExchangePlayerIter() const;
	void ErasePlayerById( const char* id );
	//ɾ������
	void ErasePlayerById( const char* id_1, const char* id_2 );
	//�Ƿ���Ҫ�Զ�ѡ����Ա
	bool IsNeedAutoSelectPlayer() const;
	//ͨ�������Զ�ѡ����Ա
	bool AutoSelectPlayerBySend();
	//�����׷����油
	bool SetFirstSecondPlayers( const Json::Value& players_array );
	//������Ա������
	bool SetTotalPlayersCnt( const Json::Value& json_players_cnt );
	//�����׷�
	void SetFirstPlayers( const Json::Value& players_array );
	//�����油
	void SetSecondPlayers( const Json::Value& players_array );
	//��������ĳ��ְλ����Ա�ĵ�����
	SharedPlayerIter CreatePlayerIterByPosition( GType::enPlayerPosition player_position[], int position_cnt ) const;
	//��������ĳ��ְλ����ʣ���������Ϊ0����Ա�ĵ�����
	SharedPlayerIter CreateRubbishPlayerIterByPosition( GType::enPlayerPosition player_position[], int position_cnt ) const;
	//��������ĳ��ְλ����ʣ�����������Ϊ0����Ա�ĵ�����
	SharedPlayerIter CreateNoRubbishPlayerIterByPosition( GType::enPlayerPosition player_position[], int position_cnt ) const;
	//��Լָ��ְλ����Ҫ��Լ����Ա
	bool ContractPlayersByPosition( GType::enPlayerPosition player_position[], int position_cnt );
	//��Լ�׷����油����Ҫ��Լ����Ա
	bool ContractFirstAndSecondPlayers();
	//�����Զ�����
	void SendAutoMatch();
	//�Ƿ����Զ�ȯ
	bool HasAutoMatchTicket();
	//�Զ�����ȯ������
	int AutoMatchTicketCnt();
	//�Զ�ʹ��ָ���������Զ�����ȯ
	void UseSomeAutoMatchTicket( int cnt );
	//һ����Ա������
	int GetFirstTeamCnt() const;
	//������Ա������
	int GetSecondTeamCnt() const;
	//�õ����Ա������
	int GetThirdPlayerCnt() const;
	//�õ�ָ��ְλ������
	int GetThePosPlayersCnt( GType::enPlayerPosition pos ) const;
	//һ����Ա�ĵ�����
	SharedPlayerIter CreateFirstTeamIter() const;
	//�����׷����油
	bool SendFirstAndSecondPlayersInfo() const;
	bool SendFirstAndSecondPlayersSync( const PlayerContT& first_second_players );
	//���׷����油��ʣ�����Ϊ0�ĸ�����
	std::pair<bool, bool> DegradeFirstAndSecond();
	std::pair<bool, bool> DegradeFirstAndSecondSync();
	void LuaDegradeFirstAndSecondSync();
	//�õ���Ա������
	int GetAllPlayersCnt() const;
	//�Ƿ���Ҫ�����Ա
	bool IsNeedFirePlayer() const;
	//�Զ������Ա
	bool AutoFirePlayers();
	//�Ƿ�ѡ��������
	bool IsSelectedSickEnemy();
	//�Զ�ѡ������
	void AutoSelectSickEnemy();
	//���ö�����Ϣ
	void SetEnemyInfo( const Json::Value& json_enemy_info );
	//������Ա�У�ʣ��������β�Ϊ0�����������ɲμӱ���������
	int CanJoinedPlayersCnt() const;
	//�������к��ʣ�����Ϊ0����Ա
	bool DegradeAllThirdRubbishPlayers();
	//�������к���ͬ������Ա
	bool DegradeAllThirdSamePlayers();
	//�������Ա
	bool FillFullThirdPlayers();
	//�Ƿ���Ҫ�������Ա
	bool NeedSupplyThirdPlayers() const;
	//�ڱ��������ʱ���Ƿ�ʱ
	bool IsTimeoutAtMatchRoom() const;
	//���ñ��������Ƿ�ʱ�ı�־
	void ResetTimeoutAtMatchRoom();
	//�õ��������䳬ʱ�ļ�ʱ��
	IoTimerPtr GetTimer_AtMatchRoom( std::size_t milli_seconds );
	//Ѱ��ָ��spid����Ա
	stPlayer* FindPlayerBySpid( int spid );
	//���óɾ���Ϣ
	void SetAchievementInfo( const Json::Value& achievements );
	//���������Ϣ
	bool SetGiftPackageInfo( const Json::Value& json_gp );
	//��ڼ���GP���
	bool BuyGiftPackageByIdx( int idx );
	//�Ƿ������ĳ�����������
	bool CanBuyGiftPackage( int idx ) const;
	//����ƣ��
	void SetMatchAddict( bool is_addict );
	//�������棬���������Ϣ
	void SendSquadInfoAtMatch();
	//�õ�ĳ��ְλ�ĵ�һ����Ա
	stPlayer* GetFirstPlayerByPosition( GType::enPlayerPosition pos );
	//������Ա�ɹ�
	void OnSellPlayerSucceed( const std::string& player_id );
	//�õ��ҵ������б�
	stSelfOfferItem::ContT& GetSelfOfferList();
	//ˢ���ҵ������б�
	void RefreshSelfOfferList();
	//�Ƿ���Ҫˢ���ҵ������б�
	bool NeedRefreshSelfOffserList() const;
	//ȡ��������Ա
	void CancelSale( const std::string& id );
	//�ҵ�һ��ָ��id�ı���������Ա
	stSelfOfferItem* FindSoldPlayer( const std::string& player_id );
	//����������Ϣ
	void SendSelfSoldInfo() const;
	//������������Ա����Ϣ
	bool GenSoldPlayersInfo( Json::Value& sold_players_info, bool against_offer_price ) const;
	//�������е�������Ϣ
	bool GenAllSoldPlayersInfo( Json::Value& sold_players_info ) const;
	//���������ų��������Ϣ
	bool GenOtherOfferItemsInfo( Json::Value& sold_players_info ) const;
	//��������ָ����������Ա
	int OpenSomePlayersAs( int cnt );
	//ʹ��һЩ��Ʒ
	int UseSomeItem( int cnt );
	//ָ����ְλ���Ƿ���ͬ������Ա
	static bool HasSamePlayerAtPos( GType::enPlayerPosition player_position[], int position_cnt, const stPlayer& player, const PlayerContT& players );
	static bool HasSamePlayerAtPos( const stPlayer& player, const PlayerContT& players );
	//ȷ��ѡ����Ա
	bool ChooseExchPlayer();
	//��ְλ��Ա�н���һЩ��Ա
	bool ExchPlayersInPosNo( int price_filter, int cnt );
	//���ձ�������Ʒ
	bool UnpackAllBags();
	//������ȡ������������Ϣ
	bool RefreshCoachMe();
	bool RefreshCoachMeImpl(bool force_refresh);
	//�����¼�
	void HandleTimeCancelSale();

	//������������Ա���
public:
	//�õ���������Ϣ
	stSellingPlayerInfo::ContT& GetSellingPlayers();
	//�õ����¼۸�
	stSellingPriceRange::ContT& GetSellingPrice();
	//Ѱ��һ��������
	stSellingPlayerInfo* FindSellingPlayer( const stOfferItem& offer_item );
	//�õ���Ա�۸�Χ
	stSellingPriceRange* FindSellingPrice( int spid, int grade );
	//����ָ����Ա��������Ϣ
	bool UpdateSpecifySellingPlayer( int spid, stSellingPlayerInfo::ContT& out_selling_players );
	//����ָ����Ա��ǿ���ȼ��ļ۸�
	bool UpdateSellingPrice( int spid, int grade );
	//���������˵�������Ϣ
	bool AddOtherOffers( const Json::Value& sold_players );
	//ɾ�������˵�������Ϣ
	bool DeleteOtherOffers( const Json::Value& sold_players );
	//�����ҵ������б�����ָ���۸�ļ�����Ա������
	bool KeepSellingPlayerAs( double price, int cnt );
	//�����ҵ���Ա�������ڼ���
	bool KeepPlayersCntMoreThan( int cnt, double price_limit );
	//��������һ��������Ա
	bool KeepSellingRubbishPlayer( double price_min, double price_max );
	//��������һЩ�߼�ֵ����Ա
	bool KeepSellingGoodPlayers( int cnt, double price_limit );
	//�������Ա
	static bool Buy( int spid, int grade, double price );
	//�Ƿ���Թ���
	static bool CanBuy( double price );
	//���������˵���Ա
	bool BuyOtherPlayers();
	//��նԷ���������Ϣ
	void ClearOtherSoldInfo();
	//��Ĭ�ϼ۸�������Ա
	bool SalePlayersAsDefault( double price_lower, double price_upper );
	//����߼�����һЩ��Ա
	bool SaleSomePlayersAsMaxPrice( int player_cnt );
	//����߼�����ָ������Ա
	bool SaleThePlayersAsMaxPrice( int player_cnt, int player_id );
	//����ͼ�����һЩ��Ա
	bool SaleSomePlayersAsMinPrice( int player_cnt );
	//����ͼ�����ָ������Ա
	bool SaleThePlayersAsMinPrice( int player_cnt, int player_id );
	//��ָ���ļ۸�����һЩָ������Ա
	bool SaleThePlayersAsPrice_Cnt( int player_id, int player_cnt , double price );
	//��ָ���ļ۸�����ָ������Ա
	bool SaleThePlayersSpecific(int player_id, int grade_min, int grade_max, int player_cnt, double price);
	//��ָ���ļ۸���һ��ָ������Ա
	bool BuyThePlayerAsPrice( int player_id, int grade, double price_lower, double price_upper );
	//�ǵ�һ�ο�ʼ��ʱ˫��
	bool IsFirstCalcDoubleTime() const;
	//����˫��
	bool IsAtDoubleTime() const;
	//����˫���ʱ
	void UpdateDoubleTime();
	//����ָ����ʱ����
	bool IsAtTheTimeSpan( int time_minutes );
	//���˽ؿ�ָ����ʱ����
	bool IsJieCardTheTimeSpan( int time_minutes );
	bool IsJieCardTheTime_Sec( int time_seconds );
	//��ָ������Ա���нؿ�
	bool JieCardThePlayer( int player_id, int grade, double price );
	//ǿ��ָ������Ա
	void EnhanceThePlayer(int player_id, int dst_grade_min, int dst_grade_max, int src_grade_min, int src_grade_max);
	//ָ����Ա������
	int GetThePlayerCnt(int player_id, int grade_min, int grade_max);

	//����ֵ���
public:
	//����ָ������Ա
	void SaleSpecifyPlayers( int ability, double price );
	//���ڵ����������ֵ����Ա���ᱻ����
	int GetAbilityFilter() const;
	//����
	void SetAbilityFilter( int ability_filter );
	//���ڵ��������ֵ����Ա���ᱻ����
	double GetExchPriceFilter() const;
	//���ò��ᱻ��������Ա��ֵ
	void SetExchPriceFilter( double price_filter );
	//�߼�ֵ��ʾ
	double GetHighPriceFilter() const;
	void SetHighPriceFilter( double price_filter );
	//�Է���Ӫ������յ�������Ϣ�ļ۸�Χ
	double GetAgainstOfferPrice() const;
	void SetAgainstOfferPrice( double price );
	//�õ��ȴ�������Ա�ĳ�ʱʱ��
	int GetTimeWaitSalePlayer() const;
	//���õȴ�������Ա��ʱ�䣬��ʱ���¼�
	void SetTimeWaitSalePlayer( int time_hour );

	//�����������
public:
	//�õ�����������״̬
	GType::enCreateCoach_SubState GetCC_SubState() const;
	//���ô���������״̬
	void SetCC_SubState( GType::enCreateCoach_SubState cc_state );
	//�Ƿ��Ǵ�����������
	bool IsCreateCoachProcedure() const;
	//������ɽ�������
	std::string GenCoachName();
	//�Ƿ񴴽������ɹ�
	bool IsCreateCoachSucceed() const;
	//���ô��������ɹ�
	void SetCreateCoachSucceed( bool is_succeed );

	//�����־���
public:
	//�Ƿ����������������
	bool IsGettingGpData() const;
	//������������ı�־
	void SetGettingGpDataTag( bool is_getting );

	//�������
public:
	//�õ�һ�����Ա���������Ա
	stPlayer* GetCanBeSoldPlayer();
	void Test();

private:
	//�������е�һ����ԱΪ�
	void ResetFirstTeamPlayersToThird();
	//��������Ϣ
	bool CombineSquadInfo( Json::Value& squad_info ) const;
	//����һ������Ա
	int BuySomeOtherPlayers( int cnt, double price_limit );

private:
	struct stPlayersNormalIter : public GPlayer::stPlayerIter{
		template<typename T>
		stPlayersNormalIter( const T& filter_fn ) : filter_fn_(filter_fn){
			it_ = GPlayer::GetMe().GetAllPlayers().begin();
			NextValid();
		}
		void First() override;
		void Next() override;
		bool IsDone() const override;
		value_type CurItem() const override;

	private:
		void NextValid();

	private:
		GPlayer::PlayerContT::iterator							it_;
		boost::function<bool( const GPlayer::stPlayer& )>		filter_fn_;
	};

private:
	double					ep_;
	stLevelInfo				level_info_;					//�ȼ���Ϣ
	std::string				name_;							//��������
	PlayerContT				players_;						//������Ա
	ItemContT				items_;							//������Ʒ
	Json::Value				enemy_info_;					//������Ϣ
	int						select_enemy_cnt_;				//ѡ�������Ϣ����
	bool					is_timeout_at_match_room_;		//�ڱ��������Ƿ�ʱ
	IoTimerPtr				timer_at_match_room_;			//���������еļ�ʱ
	GType::enCreateCoach_SubState		cc_state_;			//����������״̬
	bool					create_coach_succeed_;			//�Ƿ񴴽������ɹ�
	int						ability_filter_;				//���ڵ����������ֵ����Ա���ᱻ����
	int						gp_;
	std::vector<GiftPackage>	gift_packages_;				//GP���
	bool					request_gp_data_;			//�Ƿ����������ȡGP���
	int						max_players_cnt_;

private:
	stSelfOfferItem::ContT	self_offer_list_;			//�ҵ������б�
	stOfferItem::ContT		others_offers_;				//�����˵�������
	stSellingPlayerInfo::ContT	selling_players_;		//������Ա��Ϣ
	stSellingPriceRange::ContT	selling_price_;			//�����۸�
	Poco::DateTime				time_refresh_offer_list_;	//ˢ���ҵ���Ա�б��ʱ
	Poco::DateTime				time_cancel_sale_wait_players_;		//�¼ܼ�ʱ

private:
	double					exchange_price_filter_;				//���ò��ᱻ��������ͼ۸�
	double					high_price_filter_;					//�߼�ֵ��ʾ
	double					against_offer_price_;				//�Է���Ӫ������յ�������Ϣ�ļ۸�
	int						error_sick_enemy_cnt_;				//���Ӵ���
	Poco::DateTime			time_refresh_coach_me_;				//��������ˢ�½���������Ϣ�ļ�ʱʱ��
	int						hour_wait_sale_player_;				//�ȴ�������Сʱ��
	int						match_cnt_limit_;					//�������������˾ͻ���
	boost::optional<DateTimeLocal>	double_time_;				//�Ƿ���˫��
	boost::optional<DateTimeLocal>	time_back_select_coach_;	//���ص�ѡ�������ʱ��
	boost::optional<DateTimeLocal>	time_jie_card_;				//�ؿ���ʱ
};