import numpy as np
import segyio
import matplotlib.pyplot as plt
from PIL import Image

# ============================================================

cube_1 = segyio.tools.cube(r'stack_0_18.sgy')[:, 50, :].T
cube_2 = np.loadtxt(r'filtered_output_2.txt')


photo_1 = Image.open(r'5a72a80a26e14c8c96d19f861cbdd740.jpg')
photo_1_array = np.array(photo_1)

image_2 = np.loadtxt(r'filtered_output_1.txt')

# ============================================================
plt.figure(figsize = (7, 7))

plt.subplot(121)
plt.imshow(photo_1_array)
plt.title(f'Оригинал')

plt.subplot(122)
plt.imshow(image_2)
plt.title(f'С++')


# ============================================================
plt.figure(figsize = (7, 7))

plt.subplot(121)
plt.imshow(cube_1, cmap='seismic', aspect="auto", clim = [-1, 1])
plt.title(f'Оригинал')

plt.subplot(122)
plt.imshow(cube_2, cmap='seismic', aspect="auto", clim = [-1, 1])
plt.title(f'С++')

# ============================================================

plt.show()