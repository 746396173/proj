#pragma once

typedef struct  
{
	char	str_szSkillName[64];		// ASICC ��������
	wchar_t	str_szSkillNameEx[64];		// UNICODE ��������
	DWORD	str_dwSkillLevel;			// ���ܵȼ�
	DWORD	str_dwSkillId;				// ����ID
}JFZR_SKILL_OBJ,*PJFZR_SKILL_OBJ;


class JFZRSkill
{
public:
	JFZRSkill(void);
	virtual ~JFZRSkill(void);
public:
	virtual bool TraverseSkill(void);
	PJFZR_SKILL_OBJ GetSkillObj(char* pszskillname);
public:
	JFZR_SKILL_OBJ	m_SkillObj[64];			// Ĭ��64������
	DWORD			m_dwSkillObjIndex;

// ����ר��
public:		
	CString csTxt;
	
};

class JFZRTHIEFSkill : public JFZRSkill
{
public:
	JFZRTHIEFSkill(void);
	virtual ~JFZRTHIEFSkill(void);
};