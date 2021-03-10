--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


require 'Thrift'
require 'microchat_ttypes'

EmojiPredictionServiceClient = __TObject.new(__TClient, {
  __type = 'EmojiPredictionServiceClient'
})

function EmojiPredictionServiceClient:ping()
  self:send_ping()
  self:recv_ping()
end

function EmojiPredictionServiceClient:send_ping()
  self.oprot:writeMessageBegin('ping', TMessageType.CALL, self._seqid)
  local args = ping_args:new{}
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function EmojiPredictionServiceClient:recv_ping()
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

function EmojiPredictionServiceClient:GetEmoji(text)
  self:send_GetEmoji(text)
  return self:recv_GetEmoji(text)
end

function EmojiPredictionServiceClient:send_GetEmoji(text)
  self.oprot:writeMessageBegin('GetEmoji', TMessageType.CALL, self._seqid)
  local args = GetEmoji_args:new{}
  args.text = text
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function EmojiPredictionServiceClient:recv_GetEmoji(text)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = GetEmoji_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end
EmojiPredictionServiceIface = __TObject:new{
  __type = 'EmojiPredictionServiceIface'
}


EmojiPredictionServiceProcessor = __TObject.new(__TProcessor
, {
 __type = 'EmojiPredictionServiceProcessor'
})

function EmojiPredictionServiceProcessor:process(iprot, oprot, server_ctx)
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

function EmojiPredictionServiceProcessor:process_ping(seqid, iprot, oprot, server_ctx)
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

function EmojiPredictionServiceProcessor:process_GetEmoji(seqid, iprot, oprot, server_ctx)
  local args = GetEmoji_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = GetEmoji_result:new{}
  local status, res = pcall(self.handler.GetEmoji, self.handler, args.text)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('GetEmoji', reply_type, seqid)
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

GetEmoji_args = __TObject:new{
  text
}

function GetEmoji_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.STRING then
        self.text = iprot:readString()
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

function GetEmoji_args:write(oprot)
  oprot:writeStructBegin('GetEmoji_args')
  if self.text ~= nil then
    oprot:writeFieldBegin('text', TType.STRING, 1)
    oprot:writeString(self.text)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

GetEmoji_result = __TObject:new{
  success
}

function GetEmoji_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.STRUCT then
        self.success = Emoji:new{}
        self.success:read(iprot)
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

function GetEmoji_result:write(oprot)
  oprot:writeStructBegin('GetEmoji_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.STRUCT, 0)
    self.success:write(oprot)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end