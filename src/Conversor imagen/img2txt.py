from PIL import Image
import numpy as np

# Abre la imagen y la convierte a escala de grises
# Ruta relativa de la imagen ejecutando el script desde el direcotrio raíz del proyecto
img = Image.open("Imagenes/Torre_1080.jpg").convert("L")
arr = np.array(img)

# Guardar la matriz en un fichero .txt
# Ruta relativa del txt ejecutando el script desde el direcotrio raíz del proyecto
np.savetxt("txt/Torre_1080.txt", arr, fmt="%d")