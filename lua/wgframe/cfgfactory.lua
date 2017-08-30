require("CmnBase")
cfgfactory = {
    cfg = nil,
    --------------
    NewDftMainCfgTbl_ = nil,
    NewDftCfgTbl_ = nil,
    NewMainSmartCfg_ = nil,
    NewSmartCfg_ = nil,
    NewCfgWrapper_ = nil,
}

ConsoleCfgFactory = {
    __index = cfgfactory,
    -----------------
    NewDftMainCfgTbl_ = nil,
    NewDftCfgTbl_ = nil,
    NewMainSmartCfg_ = nil,
    NewSmartCfg_ = nil,
    NewDftAcGlobalTbl_ = nil,
	NewAcGlobalCfgOper_ = nil,
    NewCfgWrapper_ = nil,
    NewAcListOper_ = nil,
	NewAcListItemOper_ = nil,
    NewStateNameMap_ = nil,
}
setmetatable(ConsoleCfgFactory, ConsoleCfgFactory)

function cfgfactory:NewDftMainCfgTbl_(cfgInfo, ...)
    return { version = 1 }
end

function cfgfactory:NewDftCfgTbl_(cfgInfo, ...)
	return {}
end

function cfgfactory:NewMainSmartCfg_(cfgInfo, ...)
	return {}
end

function cfgfactory:NewSmartCfg_(cfgInfo, ...)
	return {}
end

function cfgfactory:NewCfgWrapper_(cfgTbl, parentName, key)
end

function ConsoleCfgFactory:NewDftMainCfgTbl_(cfgInfo, ...)
	local cfg = cfgfactory.NewDftMainCfgTbl_(self, cfgInfo, ...)
	cfg.acList = {}
    cfg.loginAcInfo = {}
	return cfg
end

function ConsoleCfgFactory:NewDftCfgTbl_(cfgInfo, ...)
	local cfgName = cfgInfo.cfgName
	if cfgName == self.cfg:GetAcCfgFullName(self.cfg.acGlobalCfgName) then
		return self:NewDftAcGlobalTbl_()
	end
	return cfgfactory.NewDftCfgTbl_(self, cfgInfo, ...)
end

function ConsoleCfgFactory:NewMainSmartCfg_(cfgInfo, ...)
	local cfg = cfgfactory.NewMainSmartCfg_(self, cfgInfo, ...)
	CmnBase.SelfMetaForwardSet(cfg, "__index", self.cfg.MainCfgOper)
	return cfg
end

function ConsoleCfgFactory:NewSmartCfg_(cfgInfo, ...)
	local cfgName = cfgInfo.cfgName
	if cfgName == self.cfg:GetAcCfgFullName(self.cfg.acGlobalCfgName) then
		local cfg = self:NewAcGlobalCfgOper_()
		CmnBase.SelfMetaForwardSet(cfg, "__index", self.cfg.AcGlobalCfgOper)
		return cfg
	end
	return cfgfactory.NewSmartCfg_(self, cfgInfo, ...)
end

function ConsoleCfgFactory:NewDftAcGlobalTbl_()
	return {
        checked = true,
		autoRun = false,
		script = "test",
        rolesInfo = {},
        timeRestricted = 0,
	}
end

function ConsoleCfgFactory:NewAcGlobalCfgOper_()
	return {}
end

function ConsoleCfgFactory:NewCfgWrapper_(cfgTbl, parentName, key)
    local cfgMgr = self.cfg
	local mainCfgName = cfgMgr.mainCfgName
	if parentName == mainCfgName then
		if key == "acList" then
			local cfg = {}
			CmnBase.SelfMetaForwardSet(cfg, "__index", self:NewAcListOper_(cfgMgr))
			return cfg
		end
	end
	if parentName == mainCfgName .. ".acList" and type(key) == "number" then
		local cfg = {}
		CmnBase.SelfMetaForwardSet(cfg, "__index", self:NewAcListItemOper_(cfgMgr))
		return cfg
	end
end

function ConsoleCfgFactory:NewAcListOper_(cfgMgr)
	return cfgMgr.AcListOper
end

function ConsoleCfgFactory:NewAcListItemOper_(cfgMgr)
	return cfgMgr.AcListItemOper
end

function ConsoleCfgFactory:NewStateNameMap_(acList)
    return {
		[acList.stateNil] = "",
        [acList.stateWaitLogin] = "�ȴ���½",
		[acList.stateLogining] = "��½��",
        [acList.stateWaitLogined] = "�ȴ�����",
        [acList.stateLogined] = "�ѵ�½",
        [acList.stateWaitRun] = "�ȴ�����",
        [acList.stateRunning] = "������",
        [acList.stateWaitStop] = "�ȴ�ֹͣ",
        [acList.stateStopped] = "��ֹͣ",
		[acList.stateTaskDone] = "�����",
        [acList.stateRolesUseout] = "��ɫˢ��",
		[acList.stateAcPwdErr] = "�ʺ��������",
		[acList.stateBan] = "�ѷ�",
		[acList.stateFreeze] = "����",
	}
end
