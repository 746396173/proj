require("s_cmncfg")
s_StateResolver = {
    resolver = nil,
    ----------
    GetResolver = nil,
    ParseStates = nil,
    SetStateRoot = nil,
    ParseSetStateRoot = nil,
    Resolve = nil,
    StateContNode = nil,
    ״̬������� = nil,
    StateUnionNode = nil,
    ״̬���Ͻ�� = nil,
    StateFindPicNode = nil,
    ״̬��ͼ��� = nil,
}

function s_StateResolver:GetResolver()
    local resolver = self.resolver
    if resolver ~= nil then return resolver end
    resolver = StateResolver(s_cmncfg.nextStateGloTimeout)
    self.resolver = resolver
    return resolver
end

function s_StateResolver:ParseStates(tbl)
    local resolver = self:GetResolver()
    return resolver:ParseStates(tbl)
end

function s_StateResolver:SetStateRoot(stateRoot)
    local resolver = self:GetResolver()
    return resolver:SetRoot(stateRoot)
end

function s_StateResolver:ParseSetStateRoot(tbl)
    local resolver = self:GetResolver()
    if resolver:GetRoot() then return end
    local stateRoot = self:ParseStates(tbl)
    if stateRoot == nil then return end
    resolver:SetRoot(stateRoot)
    return stateRoot
end

function s_StateResolver:Resolve()
    local resolver = self:GetResolver()
    while true do
        local res = resolver:Resolve()
        if res > 0 then
            LogT("s_StateResolver:Resolve���������������״̬����", res)
            break
        elseif res < 0 then
            LogD("s_StateResolver:Resolve���С��0����ʾ�����ˣ�����û���жϵ���Ϸ���ڵ�״̬�������", res)
            break
        else
            LogT("s_StateResolver:Resolve���Ϊ0����ʾû���жϵ���Ϸ���ڵ�״̬���ӳٺ��ٴ�ѭ��")
        end
        Delay(2000)
    end    
end

function s_StateResolver.StateContNode(...)
    return s_StateResolver:GetResolver():StateContNode(...)
end
s_StateResolver.״̬������� = s_StateResolver.StateContNode

function s_StateResolver.StateUnionNode(...)
    return s_StateResolver:GetResolver():StateUnionNode(...)
end
s_StateResolver.״̬���Ͻ�� = s_StateResolver.StateUnionNode

function s_StateResolver.StateFindPicNode(...)
    return s_StateResolver:GetResolver():StateFindPicNode(...)
end
s_StateResolver.״̬��ͼ��� = s_StateResolver.StateFindPicNode
