--
-- Autogenerated by Thrift
--
-- DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
-- @generated
--


local Thrift = require 'Thrift'
local TType = Thrift.TType
local __TObject = Thrift.__TObject
local TException = Thrift.TException

local ErrorCode = {
  SE_CONNPOOL_TIMEOUT = 0,
  SE_THRIFT_CONN_ERROR = 1,
  SE_UNAUTHORIZED = 2,
  SE_MEMCACHED_ERROR = 3,
  SE_MONGODB_ERROR = 4,
  SE_REDIS_ERROR = 5,
  SE_THRIFT_HANDLER_ERROR = 6,
  SE_RABBITMQ_CONN_ERROR = 7
}

local UserStatus = {
  ONLINE = 0,
  OFFLINE = 1,
  AWAY = 2
}

local ServiceException = TException:new{
  __type = 'ServiceException',
  errorCode,
  message
}

function ServiceException:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.I32 then
        self.errorCode = iprot:readI32()
      else
        iprot:skip(ftype)
      end
    elseif fid == 2 then
      if ftype == TType.STRING then
        self.message = iprot:readString()
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

function ServiceException:write(oprot)
  oprot:writeStructBegin('ServiceException')
  if self.errorCode ~= nil then
    oprot:writeFieldBegin('errorCode', TType.I32, 1)
    oprot:writeI32(self.errorCode)
    oprot:writeFieldEnd()
  end
  if self.message ~= nil then
    oprot:writeFieldBegin('message', TType.STRING, 2)
    oprot:writeString(self.message)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

local User = __TObject:new{
  userID,
  username,
  name,
  userStatus
}

function User:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.I64 then
        self.userID = iprot:readI64()
      else
        iprot:skip(ftype)
      end
    elseif fid == 2 then
      if ftype == TType.STRING then
        self.username = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 3 then
      if ftype == TType.STRING then
        self.name = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 4 then
      if ftype == TType.I32 then
        self.userStatus = iprot:readI32()
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

function User:write(oprot)
  oprot:writeStructBegin('User')
  if self.userID ~= nil then
    oprot:writeFieldBegin('userID', TType.I64, 1)
    oprot:writeI64(self.userID)
    oprot:writeFieldEnd()
  end
  if self.username ~= nil then
    oprot:writeFieldBegin('username', TType.STRING, 2)
    oprot:writeString(self.username)
    oprot:writeFieldEnd()
  end
  if self.name ~= nil then
    oprot:writeFieldBegin('name', TType.STRING, 3)
    oprot:writeString(self.name)
    oprot:writeFieldEnd()
  end
  if self.userStatus ~= nil then
    oprot:writeFieldBegin('userStatus', TType.I32, 4)
    oprot:writeI32(self.userStatus)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

local Message = __TObject:new{
  messageID,
  text,
  sender,
  recipients,
  timestamp
}

function Message:read(iprot)
  iprot:readStructBegin()
  while true do
    local fname, ftype, fid = iprot:readFieldBegin()
    if ftype == TType.STOP then
      break
    elseif fid == 1 then
      if ftype == TType.I64 then
        self.messageID = iprot:readI64()
      else
        iprot:skip(ftype)
      end
    elseif fid == 2 then
      if ftype == TType.STRING then
        self.text = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 3 then
      if ftype == TType.STRING then
        self.sender = iprot:readString()
      else
        iprot:skip(ftype)
      end
    elseif fid == 4 then
      if ftype == TType.LIST then
        self.recipients = {}
        local _etype3, _size0 = iprot:readListBegin()
        for _i=1,_size0 do
          local _elem4 = iprot:readString()
          table.insert(self.recipients, _elem4)
        end
        iprot:readListEnd()
      else
        iprot:skip(ftype)
      end
    elseif fid == 6 then
      if ftype == TType.I64 then
        self.timestamp = iprot:readI64()
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

function Message:write(oprot)
  oprot:writeStructBegin('Message')
  if self.messageID ~= nil then
    oprot:writeFieldBegin('messageID', TType.I64, 1)
    oprot:writeI64(self.messageID)
    oprot:writeFieldEnd()
  end
  if self.text ~= nil then
    oprot:writeFieldBegin('text', TType.STRING, 2)
    oprot:writeString(self.text)
    oprot:writeFieldEnd()
  end
  if self.sender ~= nil then
    oprot:writeFieldBegin('sender', TType.STRING, 3)
    oprot:writeString(self.sender)
    oprot:writeFieldEnd()
  end
  if self.recipients ~= nil then
    oprot:writeFieldBegin('recipients', TType.LIST, 4)
    oprot:writeListBegin(TType.STRING, #self.recipients)
    for _,iter5 in ipairs(self.recipients) do
      oprot:writeString(iter5)
    end
    oprot:writeListEnd()
    oprot:writeFieldEnd()
  end
  if self.timestamp ~= nil then
    oprot:writeFieldBegin('timestamp', TType.I64, 6)
    oprot:writeI64(self.timestamp)
    oprot:writeFieldEnd()
  end
  oprot:writeFieldStop()
  oprot:writeStructEnd()
end

return{
  ErrorCode=ErrorCode,
  User=User,
  Message=Message,
  UserStatus=UserStatus,
  ServiceException=ServiceException
}