player = {
    position = {
    x = 32.5, y = 20.0
    },
    filename = "sprite.png",
    HP = 300
}

array = {1, 1, 2, 3, 5, 10, 20}

function myluafunction(times)
  return string.rep("(-)", times)
end

function printHelloWorld(s)
	print(s)
end

function init()
	print("init player")
end

function update()
	print("update player")
end