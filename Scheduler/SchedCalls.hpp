/*
 * SchedCalls.hpp
 *
 *  Created on: May 22, 2018
 *      Author: daniel
 */

#ifndef SCHEDCALLS_HPP_
#define SCHEDCALLS_HPP_

/*
struct st_Message
{
    bool     bMessageValid;   // - True when message is valid
    uint8_t  u8DestinationID; // - Destination Task ID
    uint8_t  u8SourceID;      // - Source Task ID
    uint8_t  u8MessageCode;   // - Message code, interpreted by Destination
    uint32_t u32MessageData;  // - Message data, interpreted by Destination
    uint8_t * pPayload;       // - Message Payload, interpreted by Destination
};
*/

/**
 * Mensajes estandarizados para el scheduler y mensajes de uso común.
 *
 * Los mensajes al scheduler aplican cuando u8DestinationID == SCHED_ID.
 * Para estos mensajes u8SourceID se interpreta como el task a modificar.
 * la acción que
 * se toma depende de u8MessageCode según las siguientes constantes
 */
enum StdCall {

    /****************** Mensajes del sched ******************/
    /**
     * Activa/desactiva un task.
     *
     * Argumentos
     *      u8SourceID : ID del task
     *      u32MessageData : si es 0 desactiva el task, de lo contrario lo activa.
     */
    setTaskActive = 0,

    /**
     * Cambia un task a modo Oneshot y lo habilita.
     *
     * Argumentos
     *      u8SourceID : ID del task
     *      u32MessageData : Delay? no implementado
     */
    setTaskOneShot,

    /**
     * Cambia un task a modo periodico y lo habilita.
     *
     * Argumentos
     *      u8SourceID : ID del task
     *      u32MessageData : Periodo del task (LSB).
     */
    setTaskPeriodic,

    /****************** Mensajes comunes ******************/

    /**
     * Envía un array de datos tipo int16_t
     *
     * Argumentos
     *      u32MessageData : Tamaño del vector
     *      pPayload : Primer elemento del vector.
     */
    i16VectorMessage,

    /**
     * Envía un valor entero int16_t
     * Argumentos
     *      u32MessageData : valor
     */
    i16ScalarMessage,

    /**
     * Envia un puntero
     * Argumentos
     *      u32MessageData : Informacion adicional
     *      pPayload : El puntero
     */
    pointerMessage,
};

#endif /* SCHEDCALLS_HPP_ */
