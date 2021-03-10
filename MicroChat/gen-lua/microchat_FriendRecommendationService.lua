--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


require 'Thrift'
require 'microchat_ttypes'

FriendRecommendationServiceClient = __TObject.new(__TClient, {
  __type = 'FriendRecommendationServiceClient'
})

function FriendRecommendationServiceClient:ping()
  self:send_ping()
  self:recv_ping()
end

function FriendRecommendationServiceClient:send_ping()
  self.oprot:writeMessageBegin('ping', TMessageType.CALL, self._seqid)
  local args = ping_args:new{}
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function FriendRecommendationServiceClient:recv_ping()
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = ping_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
end

function FriendRecommendationServiceClient:GetFriendRecommendations(user)
  self:send_GetFriendRecommendations(user)
  return self:recv_GetFriendRecommendations(user)
end

function FriendRecommendationServiceClient:send_GetFriendRecommendations(user)
  self.oprot:writeMessageBegin('GetFriendRecommendations', TMessageType.CALL, self._seqid)
  local args = GetFriendRecommendations_args:new{}
  args.user = user
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function FriendRecommendationServiceClient:recv_GetFriendRecommendations(user)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = GetFriendRecommendations_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end
FriendRecommendationServiceIface = __TObject:new{
  __type = 'FriendRecommendationServiceIface'
}


FriendRecommendationServiceProcessor = __TObject.new(__TProcessor
, {
 __type = 'FriendRecommendationServiceProcessor'
})

function FriendRecommendationServiceProcessor:process(iprot, oprot, server_ctx)
  local name, mtype, seqid = iprot:readMessageBegin()
  local func_name = 'process_' .. name
  if not self[func_name] or ttype(self[func_name]) ~= 'function' then
    iprot:skip(TType.STRUCT)
    iprot:readMessageEnd()
    x = TApplicationException:new{
      errorCode = TApplicationException.UNKNOWN_METHOD
    }
    oprot:writeMessageBegin(name, TMessageType.EXCEPTION, seqid)
    x:write(oprot)
    oprot:writeMessageEnd()
    oprot.trans:flush()
  else
    self[func_name](self, seqid, iprot, oprot, server_ctx)
  end
end

function FriendRecommendationServiceProcessor:process_ping(seqid, iprot, oprot, server_ctx)
  local args = ping_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = ping_result:new{}
  local status, res = pcall(self.handler.ping, self.handler)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('ping', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
end

function FriendRecommendationServiceProcessor:process_GetFriendRecommendations(seqid, iprot, oprot, server_ctx)
  local args = GetFriendRecommendations_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = GetFriendRecommendations_result:new{}
  local status, res = pcall(self.handler.GetFriendRecommendations, self.handler, args.user)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('GetFriendRecommendations', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
end

-- HELPER FUNCTIONS AND STRUCTURES

ping_args = __TObject:new{

}

function ping_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function ping_args:write(oprot)
  oprot:writeStructBegin('ping_args')
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

ping_result = __TObject:new{

}

function ping_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function ping_result:write(oprot)
  oprot:writeStructBegin('ping_result')
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

GetFriendRecommendations_args = __TObject:new{
  user
}

function GetFriendRecommendations_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.STRUCT then
        self.user = User:new{}
        self.user:read(iprot)
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetFriendRecommendations_args:write(oprot)
  oprot:writeStructBegin('GetFriendRecommendations_args')
  if self.user ~= nil then
    oprot:writeFieldBegin('user', TType.STRUCT, 1)
    self.user:write(oprot)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

GetFriendRecommendations_result = __TObject:new{
  success
}

function GetFriendRecommendations_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.LIST then
        self.success = {}
        local _etype15, _size12 = iprot:readListBegin()
        for _i=1,_size12 do
          local _elem16 = User:new{}
          _elem16:read(iprot)
          table.insert(self.success, _elem16)
        end
        iprot:readListEnd()
      else
        iprot:skip(ftype)
      end
    else
      iprot:skip(ftype)
    end
    iprot:readFieldEnd()
  end
  iprot:readStructEnd()
end

function GetFriendRecommendations_result:write(oprot)
  oprot:writeStructBegin('GetFriendRecommendations_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.LIST, 0)
    oprot:writeListBegin(TType.STRUCT, #self.success)
    for _,iter17 in ipairs(self.success) do
      iter17:write(oprot)
    end
    oprot:writeListEnd()
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end