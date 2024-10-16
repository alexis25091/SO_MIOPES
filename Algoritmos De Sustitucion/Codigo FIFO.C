#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NUM_FRAMES 4   // NC:mero de frames (pC!ginas fC-sicas en memoria)
#define NUM_PAGES 10   // NC:mero total de pC!ginas virtuales

// Estructura para un frame de pC!gina en memoria fC-sica
typedef struct Frame {
	int page;           // NC:mero de pagina almacenada en el frame (valor -1 si estC! vacC-o)
	bool valid;         // Indica si el frame estC! ocupado (true) o vacC-o (false)
	struct Frame *prev; // Puntero al frame previo (para lista doblemente enlazada)
	struct Frame *next; // Puntero al frame siguiente (para lista doblemente enlazada)
} Frame;

// Estructura para la lista de frames en memoria fC-sica
typedef struct FrameList {
	int numFrames;      // NC:mero de frames actualmente ocupados
	Frame *head;        // Puntero al primer frame de la lista
	Frame *tail;        // Puntero al C:ltimo frame de la lista
} FrameList;

// FunciC3n para crear un nuevo frame
Frame* createFrame() {
	Frame *frame = (Frame *)malloc(sizeof(Frame));
	if (frame != NULL) {
		frame->page = -1;   // Inicialmente no hay pC!gina asignada
		frame->valid = false;
		frame->prev = NULL;
		frame->next = NULL;
	}
	return frame;
}

// FunciC3n para inicializar la lista de frames en memoria fC-sica
FrameList* createFrameList() {
	FrameList *frameList = (FrameList *)malloc(sizeof(FrameList));
	if (frameList != NULL) {
		frameList->numFrames = 0;
		frameList->head = NULL;
		frameList->tail = NULL;
	}
	return frameList;
}

// FunciC3n para insertar un frame al frente de la lista (mC!s recientemente usado)
void insertFrame(FrameList *frameList, Frame *frame) {
	if (frameList->head == NULL) {
		// Lista vacC-a
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

// FunciC3n para eliminar un frame de la lista (menos recientemente usado)
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

// FunciC3n para buscar un frame especC-fico por nC:mero de pC!gina
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

// FunciC3n para simular la carga de una pC!gina a memoria fC-sica utilizando FIFO
void loadPage(FrameList *frameList, int page) {
	Frame *frame = createFrame();
	frame->page = page;
	frame->valid = true;

	// Si la lista de frames ya estC! llena, eliminar el frame mC!s antiguo (FIFO)
	if (frameList->numFrames == NUM_FRAMES) {
		Frame *fifoFrame = frameList->tail;
		removeFrame(frameList, fifoFrame);
	}

	insertFrame(frameList, frame);
}

// FunciC3n para imprimir el estado actual de la lista de frames (solo para fines de depuraciC3n)
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

	// Simular la carga de varias pC!ginas a memoria fC-sica
	loadPage(frameList, 1);
	loadPage(frameList, 2);
	loadPage(frameList, 3);
	loadPage(frameList, 4);
	printFrameList(frameList);  // DeberC-a imprimir el estado actual de los frames

	// Intentar cargar otra pC!gina cuando todos los frames estC!n ocupados
	loadPage(frameList, 5);
	printFrameList(frameList);  // DeberC-a imprimir el estado actual despuC)s de la sustituciC3n

	// Liberar la memoria utilizada por la lista de frames
	free(frameList);

	return 0;
}




