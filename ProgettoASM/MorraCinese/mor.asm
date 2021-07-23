asm mor
// gioco a morra cinese nella versione 3 o 5
import StandardLibrary

signature:
	enum domain Gametype = {TRE|CINQUE}
	enum domain Sign3 = {PAPER | SCISSOR | ROCK}
	enum domain Sign5 = {PAPER5 | SCISSOR5 | ROCK5 | LIZARD | SPOCK}
	enum domain Result = {WINFIRST | WINSECOND | DRAW}

	dynamic monitored gameChoice: Gametype // vado a selezionare la modalita'† di gioco
	dynamic monitored userChoice3: Sign3 //scelta dell'utente
	dynamic monitored userChoice5: Sign5 //scelta dell'utente

	dynamic controlled computerChoice3: Sign3 //scelta del computer
	dynamic controlled computerChoice5: Sign5 //scelta del computer
	dynamic controlled outMess: String //stampa a video del risultato della partita

	static playResult3: Prod(Sign3, Sign3) -> Result //ritorna il risultato del gioco 3
	static playResult5: Prod(Sign5, Sign5) -> Result //ritorna il risultato del gioco 5

definitions:

	// Per comodit√† vado a definire
	// una sola funzione che va bene sia per gioco 1 che gioco 2
	function playResult3($s1 in Sign3, $s2 in Sign3) =
		if($s1=$s2) then //tre casi
			DRAW
		else
			switch($s1, $s2)
				case (SCISSOR, PAPER):
					WINFIRST
				case (PAPER, ROCK):
					WINFIRST
				case (ROCK, SCISSOR):
					WINFIRST
				otherwise //i tre casi rimanenti
					WINSECOND
			endswitch
		endif

	function playResult5($s3 in Sign5, $s4 in Sign5) =
		if($s3=$s4) then //tre casi
			DRAW
		else
			switch($s3, $s4)
				// casi scissor
				case (SCISSOR5, PAPER5):
					WINFIRST
				case (SCISSOR5, LIZARD):
					WINFIRST
				// casi paper
				case (PAPER5, ROCK5):
					WINFIRST
				case (PAPER5, SPOCK):
					WINFIRST
				// casi rock	
				case (ROCK5, SCISSOR5):
					WINFIRST
				case (ROCK5, LIZARD):
					WINFIRST
				// casi lizard	
				case (LIZARD, SPOCK ):
					WINFIRST
				case (LIZARD, PAPER5 ):
					WINFIRST
				// casi spock		
				case (SPOCK, ROCK5):
					WINFIRST
				case (SPOCK, SCISSOR5):
					WINFIRST				
				otherwise 
					WINSECOND
			endswitch
		endif

	main rule r_Main = 
		
		// vado a specificare tutto in base alla modalita'†
		if(gameChoice = TRE) then
			choose $s in Sign3 with true do
			
			par
				computerChoice3 := $s //viene memorizzato il segno solo per vedere la giocata del computer nell'update set 
				switch(playResult3(userChoice3, $s))
					case WINFIRST:
						outMess := "Hai vinto!"
					case WINSECOND:
						outMess := "Ha vinto il computer."
					case DRAW:
						outMess := "Patta."
				endswitch
			endpar
		
		else if(gameChoice = CINQUE) then 
			choose $s1 in Sign5 with true do
			
		
			par
				computerChoice5 := $s1 //viene memorizzato il segno solo per vedere la giocata del computer nell'update set 
				switch(playResult5(userChoice5, $s1))
					case WINFIRST:
						outMess := "Hai vinto!"
					case WINSECOND:
						outMess := "Ha vinto il computer."
					case DRAW:
						outMess := "Patta."
				endswitch
			endpar
		endif
		
		endif
		
default init s0:
	function outMess = ""
	function gameChoice = TRE
