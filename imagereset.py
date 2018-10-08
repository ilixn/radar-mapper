from PIL import Image, ImageDraw

source_img = Image.new('1', (600, 600), "white")

#draw = ImageDraw.Draw(source_img)
#draw.rectangle([50, 50, 300, 200], fill="black") #x0, y0, x1, y1

source_img.save("test.jpg", "JPEG")