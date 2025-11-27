from PIL import Image
import numpy as np

# Abre la imagen y la convierte a escala de grises
# Ruta relativa de la imagen ejecutando el script desde el direcotrio raíz del proyecto
img = Image.open("Imagenes/Eiffelturm.JPG").convert("L")  # "L" → grayscale
arr = np.array(img)  # arr.shape = (alto, ancho), valores 0-255

# Guardar la matriz en un fichero .txt
# Ruta relativa del txt ejecutando el script desde el direcotrio raíz del proyecto
np.savetxt("txt/Eiffelturm.txt", arr, fmt="%d")