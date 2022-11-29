#include "startup.h"
#include <string.h>
#include <stdint.h>
#include "Sound/midiMessage.h"

TIM_HandleTypeDef htim3;
static uint8_t FirstNote0 = 48; //Nota C2
static uint8_t FirstNote1 = 48; //Nota C2
static uint64_t KeypadState = 0; //estado do teclado
static uint64_t NoteBit; //posição do estado da tecla
static uint8_t Note = 0; //nota (0 a 48 -> 49 teclas)
static uint8_t SNote = 48; //SNote = 0: somente canal 1, SNote = 48: somente canal 0
static uint8_t Velocit = 96; //velocidade da nota (varia de 64 a 127)
static uint8_t KOut = 0; //saída para varredura do teclado
static uint8_t KInp = 0; //entrada para varredura do teclado
static uint8_t Split = 0; //divisão do teclado: 0 - não dividido, 1 - dividido
static uint8_t Shift = 0; //shift: 0 - destivado, 1 - ativado

void initialize()
{
}

void setup()
{
}

void keypad_scan()
{
	for(KOut = 0; KOut < 8; KOut++)
	{
		//coloca todas as saídas em nível 1
		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 \
				| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7, GPIO_PIN_SET);
		switch(KOut) //coloca uma saída em nível 0
		{
			case 0:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
				break;
			case 1:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1, GPIO_PIN_RESET);
				break;
			case 2:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);
				break;
			case 3:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET);
				break;
			case 4:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
				break;
			case 5:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
				break;
			case 6:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);
				break;
			case 7:
				HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
				break;
		}
		for(KInp = 0; KInp < 7; KInp++) //testa o estado de todas as entradas
		{
			Note = (KInp * 8) + KOut; //obtem a nota
			NoteBit = 1;
			NoteBit <<= Note;
			switch(KInp)
			{
				case 0:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 1:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_9) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 2:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_10) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 3:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_11) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 4:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 5:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
				case 6:
					if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) key_pressed(); //tecla pressionada
					else key_unpressed(); //tecla não pressionada
					break;
			}
		}
		HAL_Delay(1);
	}
}

void key_pressed()
{
	if(!(KeypadState & NoteBit)) //estava pressionada?
	{ //não
		KeypadState |= NoteBit; //sinaliza tecla pressionada
		if(Note >= 0 && Note <= 48) //nota dentro do intervalo válido?
		{ //sim
			if(Split == 1) //Split ativado?
			{ //sim
				SNote = Note; //define a divisão do teclado
				if(SNote == 48) beep(1, 100,100); //1 bip curto
				else if(SNote == 0) beep(2, 100, 100); //2 bips curtos
				else  beep(3, 100, 100); //3 bips curtos
			}
			else
			{ //não, toca a nota pressionada
				if(SNote == 48) //somente canal 0?
				{ // sim
					midiMessage(MIDI_NOTE_ON, 0, FirstNote0 + Note, Velocit); //envia mensagem
				}
				else if(SNote == 0) //somente canal 1?
				{ //sim
					midiMessage(MIDI_NOTE_ON, 1, FirstNote1 + Note, Velocit); //envia mensagem
				}
				else
				{ //canal 0 e canal 1 (teclado dividido
					if(Note < SNote) //teclas do canal 0?
					{ //sim
						midiMessage(MIDI_NOTE_ON, 0, FirstNote0 + Note, Velocit); //envia mensagem
					}
					else
					{ //não, teclas do canal 1
						midiMessage(MIDI_NOTE_ON, 1, FirstNote1 + Note, Velocit); //envia mensagem
					}
				}
			}
		}
		else if(Note == 49) //função SHIFT?
		{ //sim
			Shift = 1; //ativa
		}
		else if(Note == 50) //função SPLIT?
		{ //sim
			Split = 1; //ativa
		}
		else if(Note == 51) //função <OCT?
		{ //sim
			if(Shift == 1) //Shif ativado?
			{ //sim
				FirstNote1 += 12; //desloca uma oitava para direita
				if(FirstNote1 > 72)
				{
					FirstNote1 = 72; //limita em C4
					beep(1, 500, 100); //1 bip longo
				}
				else beep(1, 100, 100); //um bip curto
			}
			else
			{ //não
				FirstNote0 += 12; //desloca uma oitava para direita
				if(FirstNote0 > 72)
				{
					FirstNote0 = 72; //limita em C4
					beep(1, 500, 100); //1 bip longo
				}
				else beep(1, 100, 100); //um bip curto
			}
		}
		else if(Note == 52) //função OCT>?
		{ //sim
			if(Shift == 1) //Shif ativado?
			{ //sim
				FirstNote1 -= 12; //desloca uma oitava para esquerda
				if(FirstNote1 < 24)
				{
					FirstNote1 = 24; //limita em C0
					beep(1, 500, 100); //1 bip longo
				}
				else beep(1, 100, 100); //um bip curto
			}
			else
			{ //não
				FirstNote0 -= 12; //desloca uma oitava para esquerda
				if(FirstNote0 < 24)
				{
					FirstNote0 = 24; //limita em C0
					beep(1, 500, 100); //1 bip longo
				}
				else beep(1, 100, 100); //um bip curto
			}
		}
		else if(Note == 53) //função <VEL?
		{ //sim
			if(Velocit == 127) Velocit = 128; //ajusta para subtrair
			if(Velocit -= 8); //diminui a velocidade
			if(Velocit < 64)
			{
				Velocit = 64; //limita em 64
				beep(1, 500, 100); //1 bip longo
			}
			else beep(1, 100, 100); //um bip curto
		}
		else if(Note == 54) //função VEL>?
		{ //sim
			Velocit += 8; //aumenta a velocidade
			if(Velocit > 127)
			{
				Velocit = 127; //limita em 127
				beep(1, 500, 100); //1 bip longo
			}
			else beep(1, 100, 100); //um bip curto
		}
	}
}

void key_unpressed()
{
	if(KeypadState & NoteBit) //estava pressionada?
	{ //sim
		KeypadState &= ~(NoteBit); //muda sinalização da tecla
		if(Note >= 0 && Note <= 48) //nota dentro do intervalo válido?
		{ //sim
			if(SNote == 48) //somente canal 0?
			{ // sim
				midiMessage(MIDI_NOTE_OFF, 0, FirstNote0 + Note, 0); //envia mensagem
			}
			else if(SNote == 0) //somente canal 1?
			{ //sim
				midiMessage(MIDI_NOTE_OFF, 1, FirstNote1 + Note, 0); //envia mensagem
			}
			else
			{ //canal 0 e canal 1 (teclado dividido
				if(Note < SNote) //teclas do canal 0?
				{ //sim
					midiMessage(MIDI_NOTE_OFF, 0, FirstNote0 + Note, 0); //envia mensagem
				}
				else
				{ //não, teclas do canal 1
					midiMessage(MIDI_NOTE_OFF, 1, FirstNote1 + Note, 0); //envia mensagem
				}
			}
		}
		else if(Note == 49) //função SHIFT?
		{ //sim
			Shift = 0; //desativa
		}
		else if(Note == 50) //função SPLIT?
		{ //sim
			Split = 0; //desativa
		}
	}
}

void beep(uint8_t Qte, uint16_t On, uint16_t Off)
{
	uint8_t n;
	for(n = 0; n < Qte; n++)
	{
		HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_2);
		HAL_Delay(On);
		HAL_TIM_PWM_Stop(&htim3, TIM_CHANNEL_2);
		HAL_Delay(Off);
	}
}
