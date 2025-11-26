from PIL import Image
import numpy as np

# Abre la imagen y la convierte a escala de grises
img = Image.open("../Imagenes/Eiffelturm.jpg").convert("L")  # "L" → grayscale
arr = np.array(img)  # arr.shape = (alto, ancho), valores 0-255

# Guardar la matriz en un fichero .txt
np.savetxt("../txt/Eiffelturm.txt", arr, fmt="%d")