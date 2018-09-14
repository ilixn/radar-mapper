from PIL import Image, ImageFont, ImageDraw, ImageEnhance

source_img = Image.new('1', (600, 600), "white")

draw = ImageDraw.Draw(source_img)
draw.rectangle(((0, 00), (100, 100)), fill="black")

source_img.save("test.jpg", "JPEG")