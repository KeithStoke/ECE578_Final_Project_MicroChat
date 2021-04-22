local _M = {}

local function _StrIsEmpty(s)
	return s == nil or s == ''
end

local function _LoadMessages(data)
	local messages = {}
	for _, message in ipairs(data) do
		local new_message = {}
		new_message["sender"] = message.sender
		new_message["timestamp"] = tostring(message.timestamp)
		new_message["text"] = message.text
		ngx.say("Message text was ", message.text)
		table.insert(messages, new_message)
	end
	return messages
end

function _M.GetMessages()
	local MessageServiceClient = require "microchat_MessageService"
	local GenericObjectPool = require "GenericObjectPool"
	local ngx = ngx
	local cjson = require "cjson"
  	local jwt = require "resty.jwt"
  	local liblualongnumber = require "liblualongnumber"
	-- Read the parameters sent by the end user client
	
	ngx.req.read_body()
        local post = ngx.req.get_post_args()

        if (_StrIsEmpty(post.username)) then
           ngx.status = ngx.HTTP_BAD_REQUEST
           ngx.say("Incomplete arguments")
           ngx.log(ngx.ERR, "Incomplete arguments")
           ngx.exit(ngx.HTTP_BAD_REQUEST)
        end

	ngx.say("Inside Nginx Lua script: Getting all messages for ", post.username)
	
	local client = GenericObjectPool:connection(MessageServiceClient, "message-service", 9091)
	local status, ret = pcall(client.GetMessages, client, post.username)

	GenericObjectPool:returnConnection(client)


	if not status then
    
        	ngx.status = ngx.HTTP_INTERNAL_SERVER_ERROR
    		if (ret.message) then
      			ngx.header.content_type = "text/plain"
      			ngx.say("Failed to ping: " .. ret.message)
      			ngx.log(ngx.ERR, "Failed to ping: " .. ret.message)
    		else
      			ngx.header.content_type = "text/plain"
      			ngx.say("Failed to ping: " )
      			ngx.log(ngx.ERR, "Failed to pingr: " )
    		end
    		ngx.exit(ngx.HTTP_OK)
  	else
		ngx.header.content_type = "text/plain"
		ngx.say("Messages successfully retrieved: \n", ret);
  	end

end

return _M