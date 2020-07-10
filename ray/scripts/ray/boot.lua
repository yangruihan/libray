require('scripts.main')

local func = ray.update

return function()
    while func do
        ray.timer.step()
        func()
        coroutine.yield()
    end
end