import torch
from utee import selector
from PIL import Image
from torchvision import transforms
import matplotlib.pyplot as plt
import sys

model_raw, ds_fetcher, is_imagenet = selector.select('mnist', cuda=False)
	
IMG_PATH = "../pic.png"
img = Image.open(IMG_PATH).convert('L')

transforms = transforms.Compose([
    transforms.Resize((28, 28)),
    transforms.ToTensor()
    ])
img_tensor = transforms(img)

# plt.imshow(img_tensor.view(img_tensor.shape[1], img_tensor.shape[2], img_tensor.shape[0]), cmap="gray")
# plt.show()

output = model_raw (img_tensor)

res = int (output.argmax(-1).numpy()[0])

# print (res)

sys.exit(res)
