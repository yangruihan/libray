print('---main----')

function ray_load()
    print('ray_load')
end

function ray_update()
    print('ray_update', ray.timer.getDelta(), ray.timer.getFPS())
end

function ray_draw()
    print('ray_draw')
end

function ray_error(message)
    print(message)
end