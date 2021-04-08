local _M = {}

local function _StrIsEmpty(s)
	return s == nil or s == ''
end

function _M.GetUserID()
	local UserServiceClient = require "microchat_UserService"
	local GenericObjectPool = require "GenericObjectPool"
	local ngx = ngx
	-- Read the parameters sent by the end user client
	
	ngx.req.read_body()
        local post = ngx.req.get_post_args()

        if (_StrIsEmpty(post.username) ) then
           ngx.status = ngx.HTTP_BAD_REQUEST
           ngx.say("Incomplete arguments")
           ngx.log(ngx.ERR, "Incomplete arguments")
           ngx.exit(ngx.HTTP_BAD_REQUEST)
        end

	ngx.say("Inside Nginx Lua script: Getting userID...", post.username)
	
	local client = GenericObjectPool:connection(UserServiceClient, "user-service", 9090)
	local status, ret = pcall(client.GetUserID, client, post.username)

	GenericObjectPool:returnConnection(client)
	ngx.say("Status: ", status)

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
		ngx.say("UserID for given username is: ", ret)
    		ngx.exit(ngx.HTTP_OK)
  	end

end

return _M