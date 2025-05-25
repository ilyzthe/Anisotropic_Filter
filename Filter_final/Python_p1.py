import numpy as np
import segyio
from PIL import Image

photo_1 = Image.open(r'5a72a80a26e14c8c96d19f861cbdd740.jpg')
photo_1_array = np.array(photo_1)
np.savetxt("C++_photo.txt", photo_1_array)
print('C++_photo.txt сохранен!')

cube_1 = segyio.tools.cube(r'stack_0_18.sgy')[:, 100, :].T
cube_1_txt = np.savetxt('C++_cube_1.txt', cube_1)
print('C++_cube_1.txt сохранен!')


