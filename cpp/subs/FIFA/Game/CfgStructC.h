#pragma once
/*
@author zhp
@date 2014/4/9 14:55
@purpose for game cfg
*/
#include "stdafx.h"
#include "Common/XmlCfg.h"
#include <boost/serialization/version.hpp>
#include <boost/serialization/vector.hpp>
#include "Common/UsefulClass.h"

//��Ա���ݱ�
struct stPlayersData : public Singleton<stPlayersData, Singleton_Me>
{
private:
	stPlayersData();

public:
	//����
	bool Load();
	
	struct PlayerData
	{
		PlayerData();
		template<class Archive>
		void serialize( Archive & ar, const unsigned int version ){
			ar & BOOST_SERIALIZATION_NVP(spid_)
				& BOOST_SERIALIZATION_NVP(player_name_)
				& BOOST_SERIALIZATION_NVP(player_ability_);
		}

		int						spid_;
		std::string				player_name_;				//��Ա����
		int						player_ability_;			//��Ա����ֵ
	};

	template<class Archive>
	void serialize( Archive & ar, const unsigned int version ){
		ar & BOOST_SERIALIZATION_NVP(players_data_);
	}

	std::vector<PlayerData>				players_data_;

private:
	static stPlayersData				singleton_players_data;
};
BOOST_CLASS_VERSION(stPlayersData, 1)