** bfrc - Reconocimiento de caracteres por fuerza bruta**

Esta aplicacion genera un diccionario donde asocia el hash de un arhchivo de imagen (captcha) con su contenido (valor).
Fue programado con la intecion de demostrar los conocimientos adquiridos en la materia Fundamentos de Computación I (segundo año),
de la Facultad de Ingeníera de Obera-Misiones.

Este trabajo fue realizado solo con fines educativos, cualqueir uso fuera de este contecto queda bajo su responsabilidad.

---

Modo de empleo:  bfcr -f [FICHERO]]
Calcula el hash con el cifrado Adler32 del archivo, luego busca en su base de dato el valor asociado,
si lo encuentra devuelve [OK: (valor)]
En el caso que no encuentre el registro en la base de dato devuelve Error:Este Hash no esta registrado.

Opción de ayuda:
 -h	Mostrar opciones de ayuda

Opciones de la aplicación:
 -f	Archivo de imagen, la app retorna el valor asociado con el formato Ok:[value],
	si no esta registrado devuelve Error:Este Hash no esta registrado.
 -v	Esta opción es para registrar el valor al Hash asociado al archivo indicado en '-f [FICHERO]',
	si el Hash ya esta registrado se ignora el registro y retorna Error:La clave [HASH] ya existe,
	si la operación de registro tiene excito devuelve Ok:Clave registrada.
 -w	Esta opción es para registrar el valor al Hash asociado al archivo indicado en '-f [FICHERO]'
	si ese Hash ya esta registrado entonces sobre escribe el valor existente.
 -c	Calcula el hash (Adler-32) del archivo indicado en la opción '-f [FICHERO]',
	la app devuelve Hash:[0xVALUE] en hexadecimal.
 -d	Indica que base de dato utilizar, si no se especifica la opción '-d database',
	entonces crea una por defecto llamada 'datos.bin'.

---
* Version: 0.0.20
Version: 0.0.10
---




