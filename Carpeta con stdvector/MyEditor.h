#ifndef MYEDITOR_H
#define MYEDITOR_H

// Editor de texto estilo nano, hecho solo con char[] y algoritmos propios.
//   texto: arreglo que se edita (se modifica en el mismo arreglo)
//   tam:   tamano total del arreglo (incluye el '\0'); ej. sizeof(nueva.abstract)
// Devuelve true si el texto quedo distinto al que tenia al abrir el editor.
bool editorNano(char texto[], int tam);

#endif
