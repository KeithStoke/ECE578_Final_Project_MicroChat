--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


require 'Thrift'
require 'microchat_ttypes'

DatabaseServiceClient = __TObject.new(__TClient, {
  __type = 'DatabaseServiceClient'
})

function DatabaseServiceClient:ping()
  self:send_ping()
  self:recv_ping()
end

function DatabaseServiceClient:send_ping()
  self.oprot:writeMessageBegin('ping', TMessageType.CALL, self._seqid)
  local args = ping_args:new{}
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function DatabaseServiceClient:recv_ping()
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

function DatabaseServiceClient:WriteToDatabase(query)
  self:send_WriteToDatabase(query)
  return self:recv_WriteToDatabase(query)
end

function DatabaseServiceClient:send_WriteToDatabase(query)
  self.oprot:writeMessageBegin('WriteToDatabase', TMessageType.CALL, self._seqid)
  local args = WriteToDatabase_args:new{}
  args.query = query
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function DatabaseServiceClient:recv_WriteToDatabase(query)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = WriteToDatabase_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end

function DatabaseServiceClient:ReadFromDatabase(query)
  self:send_ReadFromDatabase(query)
  return self:recv_ReadFromDatabase(query)
end

function DatabaseServiceClient:send_ReadFromDatabase(query)
  self.oprot:writeMessageBegin('ReadFromDatabase', TMessageType.CALL, self._seqid)
  local args = ReadFromDatabase_args:new{}
  args.query = query
  args:write(self.oprot)
  self.oprot:writeMessageEnd()
  self.oprot.trans:flush()
end

function DatabaseServiceClient:recv_ReadFromDatabase(query)
  local fname, mtype, rseqid = self.iprot:readMessageBegin()
  if mtype == TMessageType.EXCEPTION then
    local x = TApplicationException:new{}
    x:read(self.iprot)
    self.iprot:readMessageEnd()
    error(x)
  end
  local result = ReadFromDatabase_result:new{}
  result:read(self.iprot)
  self.iprot:readMessageEnd()
  if result.success ~= nil then
    return result.success
  end
  error(TApplicationException:new{errorCode = TApplicationException.MISSING_RESULT})
end
DatabaseServiceIface = __TObject:new{
  __type = 'DatabaseServiceIface'
}


DatabaseServiceProcessor = __TObject.new(__TProcessor
, {
 __type = 'DatabaseServiceProcessor'
})

function DatabaseServiceProcessor:process(iprot, oprot, server_ctx)
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

function DatabaseServiceProcessor:process_ping(seqid, iprot, oprot, server_ctx)
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

function DatabaseServiceProcessor:process_WriteToDatabase(seqid, iprot, oprot, server_ctx)
  local args = WriteToDatabase_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = WriteToDatabase_result:new{}
  local status, res = pcall(self.handler.WriteToDatabase, self.handler, args.query)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('WriteToDatabase', reply_type, seqid)
  result:write(oprot)
  oprot:writeMessageEnd()
  oprot.trans:flush()
end

function DatabaseServiceProcessor:process_ReadFromDatabase(seqid, iprot, oprot, server_ctx)
  local args = ReadFromDatabase_args:new{}
  local reply_type = TMessageType.REPLY
  args:read(iprot)
  iprot:readMessageEnd()
  local result = ReadFromDatabase_result:new{}
  local status, res = pcall(self.handler.ReadFromDatabase, self.handler, args.query)
  if not status then
    reply_type = TMessageType.EXCEPTION
    result = TApplicationException:new{message = res}
  else
    result.success = res
  end
  oprot:writeMessageBegin('ReadFromDatabase', reply_type, seqid)
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

WriteToDatabase_args = __TObject:new{
  query
}

function WriteToDatabase_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.STRING then
        self.query = iprot:readString()
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

function WriteToDatabase_args:write(oprot)
  oprot:writeStructBegin('WriteToDatabase_args')
  if self.query ~= nil then
    oprot:writeFieldBegin('query', TType.STRING, 1)
    oprot:writeString(self.query)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

WriteToDatabase_result = __TObject:new{
  success
}

function WriteToDatabase_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.STRING then
        self.success = iprot:readString()
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

function WriteToDatabase_result:write(oprot)
  oprot:writeStructBegin('WriteToDatabase_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.STRING, 0)
    oprot:writeString(self.success)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

ReadFromDatabase_args = __TObject:new{
  query
}

function ReadFromDatabase_args:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.STRING then
        self.query = iprot:readString()
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

function ReadFromDatabase_args:write(oprot)
  oprot:writeStructBegin('ReadFromDatabase_args')
  if self.query ~= nil then
    oprot:writeFieldBegin('query', TType.STRING, 1)
    oprot:writeString(self.query)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

ReadFromDatabase_result = __TObject:new{
  success
}

function ReadFromDatabase_result:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 0 then
      if ftype == TType.STRING then
        self.success = iprot:readString()
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

function ReadFromDatabase_result:write(oprot)
  oprot:writeStructBegin('ReadFromDatabase_result')
  if self.success ~= nil then
    oprot:writeFieldBegin('success', TType.STRING, 0)
    oprot:writeString(self.success)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end