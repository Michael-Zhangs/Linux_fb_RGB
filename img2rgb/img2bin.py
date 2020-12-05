from PIL import Image

image = Image.open("stm32.jpg")
#image = image.convert("1")
pixels = image.load()

out_file = open("image.bin","wb")

for y in range(299):
    for x in range(450):
        for index in range(3):
            out = int(pixels[x,y][index]).to_bytes(length=1,byteorder='big')
            out_file.write(out)
            #out_file.write(pixels[x,y][0])
