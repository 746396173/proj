#pragma once
/*
@author zhp
@date 2016/11/4 15:23
@purpose Asset System Node
*/
#include "./DependSelfLib.h"
#include "AS_Filter.h"
#include "./DependExternLib.h"
#include <string>
#include <boost/filesystem/path.hpp>
#include <iosfwd>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/thread/recursive_mutex.hpp>
#include <boost/thread/lock_guard.hpp>
#include <CmnMix/Cmn_Iterator.h>
#include <luabind/luabind.hpp>


//////////////////////////////////////////////////////////////////////////
class AS_Node;
typedef boost::shared_ptr<AS_Node> AS_NodePtr;
typedef boost::weak_ptr<AS_Node> AS_NodeWeakPtr;
//////////////////////////////////////////////////////////////////////////
typedef IteratorTraits<AS_NodePtr, IterContTag_ByCopy> AS_NodeIteratorTraits;
typedef AS_NodeIteratorTraits::iterator AS_NodeIterator;
typedef AS_NodeIteratorTraits::iterator_pointer AS_NodeIteratorPtr;
//////////////////////////////////////////////////////////////////////////
typedef unsigned char AS_StrSizeT;
const AS_StrSizeT AS_kStrMaxSize = 255;
typedef unsigned char AS_DirSizeT;
//ϵͳ·����Ĭ��Ϊexe��dll����·��
const char* const AS_kSysDir = "*";
//˽��·��
const char* const AS_kPriDir = "|";
//////////////////////////////////////////////////////////////////////////
//���صĶ�������Disk
class AS_NodeDiscovery{
public:
	virtual AS_Node* DiscoverDir() const;
	virtual AS_Node* DiscoverFile() const;
};
//////////////////////////////////////////////////////////////////////////
//�����ļ���Ŀ¼ʱ���̰߳�ȫ�ģ��������������̰߳�ȫ�ģ���������һ��ֻ��ͬһ���̣߳����紴��һ��node��Ȼ��SetPath��
class AS_Node : public boost::enable_shared_from_this<AS_Node>{
	friend class AS_Factory;

public:
	typedef boost::recursive_mutex MutexT;
	//write lock
	typedef boost::lock_guard<MutexT> LockGuard;
	typedef boost::lock_guard<const AS_Node> GuardLock;
	enum enAS_NodeType{
		kDir,
		kFile,
		kRef,	//��ݷ�ʽ
	};

	//����
	enum enAS_NodeCate{
		kDisk,		//Ӳ���ϵ�
		kMemory,	//�ڴ��ϵ�
	};
	class Encryptor{
	public:
		typedef unsigned int KeyType;
		Encryptor(KeyType key);
		void Encrypt(const char* buffer, std::string::size_type size, char* out_buffer) const;
		void Decrypt(const char* buffer, std::string::size_type size, std::ostream& ostm) const;
		void Decrypt(const char* buffer, std::string::size_type size, char* out_buffer) const;

	private:
		KeyType		key_;
	};
	enum enSaveFlag{
		kSF_Unknown = 0,
		kSF_NoOverwrite = 1 << 1,
		kSF_NoCreateDir = 1 << 2,	//���·�������ڣ�Ҳ�����ȴ���·��
	};

protected:
	//��ֵԽС��Խ����ǰ�棻����ǰ������ȱ�������
	enum enAS_NodeLvl{
		kNL_FileMem = 0,
		kNL_DirMem,
		kNL_FileDisk,
		kNL_DirDisk,
		kNL_SysDir,
		kNL_PriDir,
		kNL_EmptyRef,
	};
	friend bool operator < (const AS_Node& lhs, const AS_Node& rhs);

	enum enSerializeMode{
		kSM_Sys,
		kSM_Other,
	};

public:
	AS_Node(enAS_NodeLvl node_lvl);
	AS_Node(const AS_Node& rhs);
	virtual ~AS_Node(){}
	//����ӽڵ�
	bool Add(AS_Node* sub_node, bool replace_existed = false);
	virtual bool Add(const AS_NodePtr& sub_node, bool replace_existed = false) = 0;
	//����ɾ������ڵ�
	//ֻ��ɾ���ӽڵ�
	virtual bool Erase(const AS_NodePtr& sub_node) = 0;
	//��ɾ���󱲽ڵ�
	bool Erase(const boost::filesystem::path& path);
	//ɾ�������ļ���
	virtual void EraseEmptySubDir();
	//ɾ��Ӳ���ļ����ļ���
	virtual int DeleteDisks() const;
	//���Բ�ѯ�����ڵ�ͺ󱲽ڵ�
	virtual AS_NodePtr Find(const boost::filesystem::path& path, const AS_IFilter* filter = nullptr, const AS_NodeDiscovery* discovery = nullptr) const = 0;
	//ֻ��ѯ�ӽڵ�
	virtual AS_NodePtr FindChild(const boost::filesystem::path& path, const AS_IFilter* filter = nullptr, const AS_NodeDiscovery* discovery = nullptr) const = 0;
	//��ѯ�������ѯ�����GetPath()==path�Ľڵ�
	virtual AS_NodePtr FindPosterity(const boost::filesystem::path& path, const AS_IFilter* filter = nullptr, const AS_NodeDiscovery* discovery = nullptr) const = 0;
	AS_NodePtr FindPosteritySmart(const boost::filesystem::path& path, const AS_IFilter* filter = nullptr, const AS_NodeDiscovery* discovery = nullptr) const;
	virtual void SetRefTo(const AS_NodePtr& handler);
	AS_NodePtr Parent(bool same_cate) const;
	bool SetParent(const AS_NodePtr& parent);
	AS_NodePtr GetRoot(bool same_cate) const;
	virtual AS_NodePtr GetPriDir() const;
	virtual AS_NodePtr GetSysDir() const;
	virtual enAS_NodeType GetType() const = 0;
	virtual enAS_NodeCate GetCate() const = 0;
	//����Ŀ¼�нڵ������
	enAS_NodeLvl GetNodeLvl() const;
	void SetNodeLvl(enAS_NodeLvl lvl);
	template<typename T>
	T* As(){
		return dynamic_cast<T*>(this);
	}
	void SetPath(const boost::filesystem::path& path);
	virtual void SetPath(const boost::filesystem::path& path, const AS_NodePtr& parent);
	const boost::filesystem::path& GetPath() const;
	std::string GetFileName() const;
	boost::filesystem::path GetAbsolutePath(bool same_cate = true, bool only_file_name = true, bool skip_when_parent_is_ref = false) const;
	//�õ��ļ�ϵͳ����Ŀ¼
	boost::filesystem::path GetAbsolutePath_() const;
	virtual AS_Node* Clone() const = 0;
	virtual void lock() const;
	virtual void unlock() const;
	virtual AS_NodeIteratorPtr Iterator(bool is_ref_to) const;
	AS_NodeIteratorPtr IteratorAncestor(const AS_NodePtr& ancestor, bool ancestor_first, bool include_child, bool include_ancestor_end) const;
	virtual bool Refresh(bool is_discory, const AS_NodeDiscovery* discovery = nullptr);
	virtual bool Empty() const;
	bool IsD2M() const;
	void SetD2M(bool is_disk2memory);
	virtual int GetChildCount() const = 0;
	bool SaveToDisk(const boost::filesystem::path& file_new_path, enSaveFlag flag = kSF_Unknown) const;
	virtual void clear() = 0;
	bool FileSameContent(const std::string& file_name) const;

public:
	virtual const char* ClsName() const = 0;
	//������std::ios_base::binary�ķ�ʽ������Ҳ����Ĭ���ı��ķ�ʽ������
	virtual bool Serialize(std::istream& istm);
	virtual bool Serialize(std::ostream& ostm) const;
	virtual std::string GetString() const = 0;
	//disk to memory���п��ܻ�ı�parent_����(Ϊ��Ч��)�����Ե��ú���þͲ�Ҫ���øö�����
	virtual AS_NodePtr D2M(const AS_NodeDiscovery* discovery = nullptr);
	static bool MakeDirs(const boost::filesystem::path& abs_path);

protected:
	static void RectifyPath(boost::filesystem::path& path);
	void SetPathByParent(const boost::filesystem::path& path, const AS_NodePtr& parent);
	static void CopyFrom(AS_Node& lhs, const AS_Node& rhs);

private:
	enSerializeMode GetSMode() const;
	void SetSMode(enSerializeMode mode);

private:
	static void RegForLua(lua_State* l);
	bool _Erase_(const char* path);
	AS_NodePtr _Find_(const char* path) const;
	AS_NodePtr _FindChild_(const char* path) const;
	AS_NodePtr _FindPosterity_(const char* path) const;
	AS_NodePtr _FindPosteritySmart_(const char* path) const;
	void _SetPath_(const char* path);
	void _SetPath_1(const char* path, const AS_NodePtr& parent);
	std::string _GetPath_() const;
	std::string _GetAbsolutePath_(bool same_cate, bool only_file_name, bool skip_when_parent_is_ref) const;
	AS_NodePtr _Clone_() const;
	bool _Equal_(const AS_NodePtr& rhs) const;
	AS_NodeIteratorPtr _Iterator_() const;
	AS_NodeIteratorPtr _Iterator_1(bool is_ref_to) const;
	bool _Refresh_(bool is_discory);
	AS_NodePtr _D2M_();
	bool _SaveToDisk_(const char* file_new_path) const;

private:
	AS_NodeWeakPtr				parent_;
	boost::filesystem::path		path_;
	enAS_NodeLvl				node_lvl_;

protected:
	mutable MutexT				mutex_;
	enSerializeMode				smode_;
	bool						d2m_;
};
