return function()
    while true do
        print('boot test')
        coroutine.yield()
    end
end