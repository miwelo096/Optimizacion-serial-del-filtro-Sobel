from PIL import Image
import numpy as np

# Lee la matriz de intensidades desde el fichero .txt
# Ruta relativa del txt ejecutando el script desde el direcotrio raíz del proyecto
arr = np.loadtxt("txt/Eiffelturm.txt", dtype=np.uint8)

# Convertir el array a imagen en escala de grises
img = Image.fromarray(arr, mode="L")

# Guardar la imagen reconstruida
# Ruta relativa de la imagen ejecutando el script desde el direcotrio raíz del proyecto
img.save("Imagenes/Eiffelturm_reconstruida.JPG")