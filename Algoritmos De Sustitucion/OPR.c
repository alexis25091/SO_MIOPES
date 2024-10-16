#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>>

#define NUM_FRAMES 4   // Numero de frames (paginas fisicas en memoria)
#define NUM_PAGES 10   // Numero total de pC!ginas virtuales

// Estructura para un frame de pagina en memoria fC-sica
typedef struct Frame {
	int page;           // Numero de pagina almacenada en el frame (valor -1 si esta vacio)
	bool valid;         // Indica si el frame esta ocupado (true) o vacio (false)
	struct Frame *prev; // Puntero al frame previo (para lista doblemente enlazada)
	struct Frame *next; // Puntero al frame siguiente (para lista doblemente enlazada)
} Frame;

// Estructura para la lista de frames en memoria fisica
typedef struct FrameList {
	int numFrames;      // Numero de frames actualmente ocupados
	Frame *head;        // Puntero al primer frame de la lista
	Frame *tail;        // Puntero al ultimo frame de la lista
} FrameList;

// Funcion para crear un nuevo frame
Frame* createFrame() {
	Frame *frame = (Frame *)malloc(sizeof(Frame));
	if (frame != NULL) {
		frame->page = -1;   // Inicialmente no hay pagina asignada
		frame->valid = false;
		frame->prev = NULL;
		frame->next = NULL;
	}
	return frame;
}

// Funcion para inicializar la lista de frames en memoria fisica
FrameList* createFrameList() {
	FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
	if (frameList != NULL) {
		frameList->numFrames = 0;
		frameList->head = NULL;
		frameList->tail = NULL;
	}
	return frameList;
}

// Funcion para insertar un frame al frente de la lista (mas recientemente usado)
void insertFrame(FrameList *frameList, Frame *frame) {
	if (frameList->head == NULL) {
		// Lista vacia
		frameList->head = frame;
		frameList->tail = frame;
	} else {
		// Insertar al frente de la lista
		frame->next = frameList->head;
		frameList->head->prev = frame;
		frameList->head = frame;
	}
	frameList->numFrames++;
}

// Funcion para eliminar un frame de la lista (menos recientemente usado)
void removeFrame(FrameList *frameList, Frame *frame) {
	if (frame->prev != NULL) {
		frame->prev->next = frame->next;
	} else {
		frameList->head = frame->next;
	}
	if (frame->next != NULL) {
		frame->next->prev = frame->prev;
	} else {
		frameList->tail = frame->prev;
	}
	frameList->numFrames--;
	free(frame);
}

// Funcion para buscar un frame especifico por numero de pagina
Frame* findFrame(FrameList *frameList, int page) {
	Frame *current = frameList->head;
	while (current != NULL) {
		if (current->page == page) {
			return current;
		}
		current = current->next;
	}
	return NULL;
}

// Funcion para simular la carga de una pagina a memoria fisica utilizando The Optimal Page Replacement Algorithm
void loadPage(FrameList *frameList, int page, int futureAccess[]) {
	Frame *frame = createFrame();
	frame->page = page;
	frame->valid = true;

	// Si la lista de frames ya esta llena, determinar la pagina optima a reemplazar
	if (frameList->numFrames == NUM_FRAMES) {
		Frame *optimalFrame = NULL;
		int farthest = -1;

		// Buscar el frame que contiene la pagina que no sera utilizada por mas tiempo
		for (int i = 0; i < NUM_FRAMES; ++i) {
			Frame *current = frameList->head;
			int j = 0;
			while (current != NULL && current->page != -1 && current->page != futureAccess[j]) {
				current = current->next;
				++j;
			}
			if (current == NULL || current->page == -1) {
				optimalFrame = current;
				break;
			}
			if (j > farthest) {
				farthest = j;
				optimalFrame = current;
			}
		}

		// Remover el frame optimo encontrado
		if (optimalFrame != NULL) {
			removeFrame(frameList, optimalFrame);
		}
	}

	// Insertar el nuevo frame en la lista de frames
	insertFrame(frameList, frame);
}

// Funcion para imprimir el estado actual de la lista de frames (solo para fines de depuracion)
void printFrameList(FrameList *frameList) {
	printf("Estado actual de la lista de frames:\n");
	Frame *current = frameList->head;
	while (current != NULL) {
		printf("PC!gina: %d, ", current->page);
		if (current->valid) {
			printf("Estado: Ocupado\n");
		} else {
			printf("Estado: VacC-o\n");
		}
		current = current->next;
	}
	printf("\n");
}

int main() {
	FrameList *frameList = createFrameList();

	// Simular el orden de accesos futuro a las pC!ginas (simplificado)
	int futureAccess[NUM_PAGES] = {1, 2, 3, 4, 5, 1, 2, 1, 3, 4};

	// Simular la carga de paginas a memoria fisica utilizando el algoritmo The Optimal Page Replacement Algorithm
	for (int i = 0; i < NUM_PAGES; ++i) {
		loadPage(frameList, futureAccess[i], futureAccess + i + 1);
		printFrameList(frameList);
	}

	// Liberar la memoria utilizada por la lista de frames
	free(frameList);

	return 0;
}


