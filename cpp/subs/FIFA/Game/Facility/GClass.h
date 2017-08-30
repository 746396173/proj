#pragma once
/*
@author zhp
@date 2014-2-18 13:26
@purpose for game class
*/
#include "GTypes.h"
#include <string>
#include "Common/GObjProxy.h"
#include "Protocol/P_Defines.h"
#include <queue>
#include "json/value.h"
#include "Common/UsefulClass.h"
#include "Net/PocoMore.h"

//#define D_SOME_LOG

namespace GClass
{
	//����http��
	class HandleHttpPackage{
		HandleHttpPackage();
		~HandleHttpPackage();
		//����http�ַ�
	public:
		static HandleHttpPackage* GetInstance();
		//����
		static void UpdateHandler( const char* http_package );
		//post string
		const char* Post();
		//get string
		const char* Get();
		//http version
		const char* HttpVersion();
		//host
		const char* Host( const char* http_package = nullptr );
		//accept
		const char* Accept();
		//cookie
		const char* Cookie( const char* http_package = nullptr );
		//connection
		const char* Connection();
		//content type
		const char* ContentType();
		//content gzip type
		const char* ContentGzipType();
		//����host
		void SetHost( const std::string& str_host );
		const std::string& GetHost() const;
		//����cookie
		void SetCookie( const Poco::Net::NameValueCollection& cookie );
		Poco::Net::NameValueCollection& GetCookie();

	public:
		//��һ��http���У�������method
		FindBetweenStringA::RangePtr GetMethodFromHttpPackage( const char* http_package ) const;
		//��һ��http���У�������uri
		FindBetweenStringA::RangePtr GetUriFromHttpPackage( const char* http_package ) const;

	public:
		//�õ�http����msg�ĵ�һ���ַ��ĵ�ַ
		static const char* GetFirstHttpMsgCharAddr( const char* str_http );
		//content type�Ƿ���json��ʽ��
		static bool ContentTypeIsJson( const char* str_http );
		//content type�Ƿ���x-gzip
		static bool ContentTypeIsXgzip( const char* str_http );

	private:
		static HandleHttpPackage*			handler_;
		std::string							host_;
		Poco::Net::NameValueCollection		cookie_;
	};
	//����http�ַ�������
	class HandleSendPackage{
		HandleSendPackage();
		//��̬����
	public:
		static HandleSendPackage& GetMe();

		//�����غ���
	public:
		//encode content length
		const char* EncodeContentLength( const char* msg );
		const char* EncodeContentLength( std::size_t msg_size );
		//���http packageͷ���Ժ���ʹ��HTTPRequest_RFB�࣬���ڻ�δ�������⣬���ҽ�����
		std::string HttpPackage_CombineNormalMsgHead( const char* msg_catalog, const char* msg );
		std::string HttpPackage_CombineNormalMsgHead( const char* msg_catalog, const std::string& msg );
		//��Ͼ���gzip�İ�ͷ
		std::string HttpPackage_CombineGzipMsgHead( const char* msg_catalog, const std::string& msg );
		//���post��Ϣ
		std::string HttpPackage_CombinePostMsgHead( const char* uri );
		
		//����http package
	public:
		//������Ϸ�еķ���
		void HandleSendPakcageOfGame( const std::string& package_send );

	private:
		//�����Ϣͷ
		std::string HttpPackage_CombineNormalMsgHead_( const char* msg_catalog );
	};

	//send http package
	class HttpPackageSend{
	private:
		HttpPackageSend();

	public:
		static HttpPackageSend& GetMe();
		//send implemental
		GType::enHttpSendCall_Result SendHttpPackage( const char* msg_head, const char* msg, std::size_t msg_size, bool is_async );
		GType::enHttpSendCall_Result SendHttpPackage( const char* msg_head, const std::string& msg, bool is_async );
		//�첽
		//static GType::enHttpSendCall_Result SendHttpPackageAsync( const char* msg_head, const char* msg );
		static GType::enHttpSendCall_Result SendHttpPackageAsync( const char* msg_head, const std::string& msg );
		//ͬ��
		//static GType::enHttpSendCall_Result SendHttpPackageSync( const char* msg_head, const char* msg );
		//����ͨ����Ϣ���첽
		//static GType::enHttpSendCall_Result SendNormalMsgAsync( const char* uri, const char* msg );
		static GType::enHttpSendCall_Result SendNormalMsgAsync( const char* uri, const std::string& msg );
		//����post��Ϣ
		static bool SendGetMsgAsync( const char* uri );
		//����ͨ����Ϣ��ͬ��
		//static GType::enHttpSendCall_Result SendNormalMsgSync( const char* uri, const char* msg );
		//����json��Ϣ���첽
		static GType::enHttpSendCall_Result SendJsonMsgAsync( const char* uri, const Json::Value& msg );
		//���ͼ�����Ϣ���첽
		static GType::enHttpSendCall_Result SendEncryptedJsonMsgAsync( const char* uri, const Json::Value& msg );
		//��ʼִ�з���
		void BeginSendHttp();
		//�����հ�����
		void EndRecvHttp();
		//���÷�������
		void ResetSendCount();
		//������ײ
		void SendPackageHit();

		//�������Ӧ��
	public:
		//����json��Ϣ���첽
		static bool Post_JsonMsgAsync( const char* uri, const Json::Value* msg );
		static bool Post_JsonMsgSync( const char* uri, const Json::Value* msg, Json::Value& respond_msg );
		//get����
		static bool Get_JsonMsgAsync( const char* uri );
		static bool Get_JsonMsgSync( const char* uri, Json::Value& respond_msg );
		//���ܵ���Ϣ
		static bool Post_EncryptJsonMsgAsync( const char* uri, const Json::Value& msg );
		static bool Post_EncryptJsonMsgSync( const char* uri, const Json::Value& msg, Json::Value& respond_msg );

		//�޸ķ������
	public:
		//�޸ķ�����Ϣ
		static void ReplaceMsg( const char* msg_head, const std::string& msg, GType::stHttpSendCall_Content* msg_src );
		static void ReplaceMsg_Uri( const char* uri, const std::string& msg, GType::stHttpSendCall_Content& msg_src );
		static void ReplaceMsg_Json( const char* uri, const Json::Value& msg, GType::stHttpSendCall_Content& msg_src );

	private:
		static GType::enHttpSendCall_Result SendHttpPackage_Impl( GType::stHttpSendCall_Content* http_content, GType::HttpSendCall_NeededObj2* obj2, 
			GType::HttpSendCall_NeededObj1* obj1, int msg_size );
		static GType::enHttpSendCall_Result DoSend_Impl( const char* http_content, std::size_t content_size );
		static void SendRequestImpl( const std::string& http_package, const std::shared_ptr<HTTPRequest_RFB>& request );
		static void SendRequestImplSync( const std::string& http_package, std::shared_ptr<HTTPResponse_RFB>& respond );

	private:
		typedef std::pair<int, int> SendCountT;

	private:
		//������������
		void RectifySendingCount();

	private:
		int					game_sending_;				//��Ϸ���ڷ���
		SendCountT			rectify_send_count_;		//������������
		DateTimeLocal		last_rec_time_;
		bool				reset_sending_cnt_;
		SharedMutex			reset_sending_mutex_;
	};

	//�����հ�
	class HandleRecvPackage{
		HandleRecvPackage();

	public:
		//�����Լ�������Ȼ�����հ�
		struct stHttpQuestInfo{
			std::string				method_;			//���󷽷�
			std::string				uri_;				//http uri

		public:
			const std::string& GetMethod() const;
			void SetMethod( const std::string& method );
			const std::string& GetUri() const;
			void SetUri( const std::string& uri );
		};

	public:
		static HandleRecvPackage& GetMe();
		//////////////////////////////////////////////////////////////////////////
		//����Ϸ�̵߳���
		//�����հ�
		void RecvHttpPackage( const char* str_http, int package_length );
		//��������İ�������Ϸ�̵߳���
		void HandleFollowPackage( const char* str_follow, size_t package_length );
		//////////////////////////////////////////////////////////////////////////
		//��ע���߳�ִ��
		//http package parse
		void RecvHttpPackageParse( const std::string& _str_http_ );
		//follow package parse
		void FollowPackageParse( const std::string& _str_follow );
		//���������İ�
		void HandleFullRecvPackage( const std::string& msg_head, const std::string& msg );
		//�õ�content-length
		static int GetContentLength( const char* str_http );
		//�õ�http msg length����http��ͷ�İ�
		static size_t GetHttpMsgLength( const char* str_http, size_t package_length );
		//http��ͷ�ĳ��ȣ���http��msg֮��ĳ���
		static int GetHttpHeaderLength(const char* str_http, int package_length);
		//�õ�������ĳ������msg����
		static size_t GetFollowMsgLength( const char* str_follow, size_t package_length );

	private:
		//�õ���һ��tag(��Ч�ַ�)�ĵ�ַ��������������ڽ���ssl_read�ײ�İɣ����ѷ�����2016/8/25 23:05
		static const char* GetFirstTagCharAddr( const char* str_package, size_t package_length );

		//�Լ����İ����Լ�����
	public:
		//ִ��һ���հ�������Ϸ���̵߳���
		void DoSllRead( const std::shared_ptr<stHttpQuestInfo>& quest );
		void DoRequest_SllRead( const std::shared_ptr<HTTPRequest_RFB>& quest );
		void DoRequest_SllReadSync( std::shared_ptr<HTTPResponse_RFB>& respond );
		//�յ�һ��������ע���̵߳���
		void OnRecvHttpResult( const std::shared_ptr<stHttpQuestInfo>& quest, const HTTPResponse_RFB& respond );
		void OnRequestHttpResult( const HTTPRequest_RFB& quest, const HTTPResponse_RFB& respond );
		//�յ�һ��json��
		void OnRecvJsonResult( const std::shared_ptr<stHttpQuestInfo>& quest, const Json::Value& result_msg );
		void OnRequestJsonResult( const HTTPRequest_RFB& quest, const Json::Value& result_msg );

	private:
		//�Ƿ�ָ����Ŀ��0���
		static bool IsSpecifyZeroTag( const char* str_package, size_t package_length );

		//type definition
	private:
		struct Sequent{
			std::string				str_anterior_;
			int						left_package_len_;
		};

	private:
		SharedMutex				mutex_handle_follow_;		//���ڴ������
		std::queue<Sequent>		sequents_;					//�к����İ�
		char					ssl_read_buffer[4000];
	};
}