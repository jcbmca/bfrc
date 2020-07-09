** bfrc - Reconocimiento de caracteres por fuerza bruta**

Esta aplicacion genera un diccionario donde asocia el hash de un arhchivo de imagen (captcha) con su contenido (valor).
Fue programado con la intecion de demostrar los conocimientos adquiridos en la materia Fundamentos de Computación I (segundo año),
de la Facultad de Ingeníera de Obera-Misiones.

Este trabajo fue realizado solo con fines educativos, cualqueir uso fuera de este contecto queda bajo su responsabilidad.

---

Modo de empleo:  bfcr -f [FICHERO]]
Calcula el hash con el cifrado Adler32 del archivo, luego busca en su base de dato el valor asociado, si lo encuentra devuelve [OK: (valor)]
En el caso que no este registrado devuelve [$ Not found!]

Modo de entrenamiento: bfcr -f [FICHERO]] -v [VALUE]
Calcula el hash con el cifrado Adler32 del archivo y asocia en la base de dato el valor que se paso con la opcion -v.

Otros parametros:
	-d [FICHERO DATOS] : Dice que base de dato se utilizara, si no esta presente este parameto entonces se crea una por defecto. (datos.bin).

---

## version: 0.0.10
---




