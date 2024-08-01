// By Grae Watson - 2024/07/10 - Colosseum King


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "attack_module.h"


#define AVATARHEIGHT 40
#define AVATARLENGTH 48
#define NUMOFAVATARS 6


CHARACTER playerToCharacter(struct Player *p)
{
	CHARACTER c;

	c.avatar = p->character.avatar;
	c.level = p->character.level;
	c.health = p->character.health;
	c.constitution = p->character.constitution;
	c.strength = p->character.strength;
	c.speed = p->character.speed;
	c.coordination = p->character.coordination;
	c.armourLevel = p->character.armourLevel;
	c.armourSkill = p->character.armourSkill;
	c.swordLevel = p->character.swordLevel;
	c.swordSkill = p->character.swordSkill;

	return c;
}


bool attackSuccess(CHARACTER attacker, CHARACTER deffender)
{
	if (1 == rand() % (20 + 1))
	{
		return true;
	}
	else 
	{
		if (attackHitAccuracy(attacker) > defenseChance(deffender))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

int attackHitAccuracy(CHARACTER attacker)
{
	return attacker.coordination + attacker.swordSkill + (rand() % (attacker.level - 0 + 1) - 0);
}

int attackPower(CHARACTER attacker)
{
	return  attacker.strength + attacker.swordLevel + (rand() % (attacker.level - 0 + 1) - 0);
}

int defenseChance(CHARACTER deffender)
{
	return deffender.speed + deffender.armourSkill + (rand() % (deffender.level - 0 + 1) - 0);
}

int defensePower(CHARACTER deffender)
{
	return deffender.constitution + deffender.armourLevel + (rand() % (deffender.level - 0 + 1) - 0);
}

FIGHTSTATUS round(CHARACTER *player, CHARACTER *enemy)
{
	if (player->speed > enemy->speed)
	{
		if (attackSuccess(*player, *enemy))
		{
			enemy->tempHealth = enemy->tempHealth - attackPower(*player);
			printf("Player Hit\n");
		}
		else
		{
			printf("Player Miss\n");
		}


		if (0 >= enemy->tempHealth)
			return PWIN;

		if (attackSuccess(*enemy, *player))
		{
			player->tempHealth = player->tempHealth - attackPower(*enemy);
			printf("Enemy Hit\n");
		}
		else
		{
			printf("Enemy Miss\n");
		}
			
	}
	else if (player->speed < enemy->speed)
	{
		if (attackSuccess(*enemy, *player))
		{
			player->tempHealth = player->tempHealth - attackPower(*enemy);
			printf("Enemy Hit\n");
		}
		else
		{
			printf("Enemy Miss\n");
		}

		if (0 >= player->tempHealth)
			return EWIN;

		if (attackSuccess(*player, *enemy))
		{
			enemy->tempHealth = enemy->tempHealth - attackPower(*player);
			printf("Player Hit\n");
		}
		else
		{
			printf("Player Miss\n");
		}
	} 
	else if (1 == ( rand() % (1 - 0 + 1) - 0 ) )
	{
		if (attackSuccess(*player, *enemy))
		{
			enemy->tempHealth = enemy->tempHealth - attackPower(*player);
			printf("Player Hit\n");
		}
		else
		{
			printf("Player Miss\n");
		}

		if (0 >= enemy->tempHealth)
			return PWIN;

		if (attackSuccess(*enemy, *player))
		{
			player->tempHealth = player->tempHealth - attackPower(*enemy);
			printf("Enemy Hit\n");
		}
		else
		{
			printf("Enemy Miss\n");
		}
	}
	else
	{
		if (attackSuccess(*enemy, *player))
		{
			player->tempHealth = player->tempHealth - attackPower(*enemy);
			printf("Enemy Hit\n");
		}
		else
		{
			printf("Enemy Miss\n");
		}

		if (0 >= player->tempHealth)
			return EWIN;

		if (attackSuccess(*player, *enemy))
		{
			enemy->tempHealth = enemy->tempHealth - attackPower(*player);
			printf("Player Hit\n");
		}
		else
		{
			printf("Player Miss\n");
		}
	}

	if (0 >= player->tempHealth)
		return EWIN;

	if (0 >= enemy->tempHealth)
		return PWIN;

	return NWIN;

}

bool attackPhase(struct Player* player)
{
	struct Enemy* enemy = initializeEnemy(SWORDSMAN);

	matchEnemyToCharacterStats(enemy, player);

	CHARACTER Enemy = enemy->character;

	CHARACTER Player = player->character;

	Player.tempHealth = Player.health = Player.constitution * 10;

	Enemy.tempHealth = Enemy.health = Enemy.constitution * 10;

	FIGHTSTATUS current = NWIN;

	printFight(Player, Enemy);

	while (NWIN == current)
	{
		current = round(&Player, &Enemy);

		printf("\n");

		printCharacterNEnemyCurrentHealth(Player, Enemy);
	}

	if (EWIN == current)
	{
		printf("You Lose\n");
		return false;
	}
	
	printf("You Won\n");
	return true;
}

void printFight(CHARACTER player, CHARACTER enemy)
{
	printCharacterNEnemyAvatar(player.avatar, enemy.avatar);

	printf("\n");

	printCharacterNEnemyStats(player, enemy);
}

//void printCharacterAvatar(int avatar)
//{
//
//}

void printCharacterNEnemyAvatar(int Pavatar, int Eavatar)
{
	char PAvatar[AVATARHEIGHT][AVATARLENGTH];
	characterAvatar(Pavatar, PAvatar);

	char EAvatar[AVATARHEIGHT][AVATARLENGTH];
	characterAvatar(Eavatar, EAvatar);

	for (int i = 0; i < AVATARHEIGHT; i++)
	{
		for (int j = 0; j < (AVATARLENGTH - 1); j++)
		{
			printf("%c", PAvatar[i][j]);
		}

		//printf("%s", PAvatar[i]);

		printf("                                 ");

		//printf("%s", EAvatar[i]);

		for (int j = 0; j < (AVATARLENGTH - 1); j++)
		{
			printf("%c", EAvatar[i][j]);
		}

		printf("\n");
	}
}

//void printCharacterStats(int avatar)
//{
//
//}

void printCharacterNEnemyStats(CHARACTER player, CHARACTER enemy)
{


	printf("Health: %d/%d", player.tempHealth, player.health);

	lineUpBasedOnNumSize(player.tempHealth);

	lineUpBasedOnNumSize(player.health);

	printf("                                                               ");

	printf("Health: %d/%d", enemy.tempHealth, enemy.health);

	printf("\n");

	printf("Strength: %d", player.strength);

	lineUpBasedOnNumSize(player.strength);
	
	printf("                                                                   ");

	printf("Strength: %d", enemy.strength);

	printf("\n");

	printf("Constitution: %d", player.constitution);

	lineUpBasedOnNumSize(player.constitution);

	printf("                                                               ");

	printf("Constitution: %d", enemy.constitution);

	printf("\n");

	printf("Speed: %d", player.speed);

	lineUpBasedOnNumSize(player.speed);

	printf("                                                                      ");

	printf("Speed: %d", enemy.speed);

	printf("\n");

	printf("Coordination: %d", player.coordination);

	lineUpBasedOnNumSize(player.coordination);

	printf("                                                               ");

	printf("Coordination: %d", enemy.coordination);

	printf("\n");

}

void printCharacterNEnemyCurrentHealth(CHARACTER player, CHARACTER enemy)
{
	printf("Health: %d/%d", player.tempHealth, player.health);

	lineUpBasedOnNumSize(player.tempHealth);

	lineUpBasedOnNumSize(player.health);

	printf("                                                               ");

	printf("Health: %d/%d", enemy.tempHealth, enemy.health);

	printf("\n");
}

void characterAvatar(int i, char* characterAvatar)
{
	char avatars[NUMOFAVATARS][AVATARHEIGHT][AVATARLENGTH] = { {
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		"                                               ",
		".-----------------------------------.          ",
		"|.---------------------------------.|          ",
		"||                 _.._            ||          ",
		"||               .'  ..=`_         ||          ",
		"||              / _ ='. )`,        ||          ",
		"||             | .--:'./`| |       ||          ",
		"||            .'    .-'   | )      ||          ",
		"||           / /:';' _   _( |      ||          ",
		"||          /.' | | '' |''| |      ||          ",
		"||         (  .|  |   __  ' /      ||          ",
		"||         |  |/ / |  `- /( |      ||          ",
		"||         )_.:./)   `--'._|       ||          ",
		"||        .'    `,    +  :))       ||          ",
		"||       /       :`;_    : |       ||          ",
		"||      |        :'::`-..',|       ||          ",
		"||     .'   .-   )::)::::::`,      ||          ",
		"||     |    /`,   |::`:::::::)     ||          ",
		"||    /    /   (  |,:::::)::/      ||          ",
		"||   /    /     (  |::::::::|      ||          ",
		"||  |   -----.o......_:::::.'      ||          ",
		"||  .         B    `-':::.':|      ||          ",
		"||  `-.-----==B-,   `.::::::|      ||          ",
		"||            /:`, `.)):::::|      ||          ",
		"||            /:::))))::::::|      ||          ",
		"||      MJP  '::::::::::'          ||          ",
		"||          (::::'                 ||          ",
		"||                                 ||          ",
		"|`---------------------------------'|          ",
		"`-----------------------------------'          "},
		{


		"                                               ",
		"                                               ",
		"                                               ",
		" _____________________________________________ ",
		"|                                             |",
		"|                _____    ____                |",
		"|             .#########.#######..            |",
		"|          .#######################.          |",
		"|        .############################.       |",
		"|       .################################.    |",
		"|      .#########,##,#####################.   |",
		"|     .#########-#,'########## ############.  |",
		"|    .######'#-##' # ##'### #. `####:#######. |",
		"|    #####:'# #'###,##' # # +#. `###:':###### |",
		"|   .####,'###,##  ###  # # #`#. -####`######.|",
		"|  .####+.' ,'#  ##' #   # # #`#`.`#####::####|",
		"|  ####'    #  '##'  #   #_'# #.## `#######;##|",
		"|  #:##'      '       #   # ``..__# `#######:#|",
		"|  #:##'  .#######s.   #.  .s######.|`#####:##|",
		"|  #:##   .'______'''    '''_____''. `.#####:#|",
		"| .#:##   ><'(##)'> )    ( <'(##)`><   `####;#|",
		"| ##:##  , , -==-' '.    .` `-==- . |  ######'|",
		"| #|-'| / /      ,  :    : ,       | ` :####:'|",
		"| :#  |: '  '   /  .     .  .  `    `  |`#### |",
		"| #|  :|   /   '  '       `  |   . ,   :  #:# |",
		"|#L. | | ,  /   `.-._ _.-.'   .  | |  : ) J## |",
		"|###| `  /  '                   |  : : |  /## | ",
		"| ## #|.:: '       _    _        ` | | |'#### |",
		"| #####|(  |  (.-'.__`-'__.`-.)   :| ' ###### |",
		"| ######|:      `-...___..-' '     :: /###### |",
		"| #######|``.                   ,'|  /####### |",
		"|.# ######|  |       ___       / /' /#######  |",
		"|# #'#####||  |    -     -    /  ,'|### #. #. |",
		"|`#  #####| '-.`             ' ,-'  |### #  # |",
		"|    #' `#|    '._         ,.-'     #`#`#.    |",
		"|         |       .'------' :       |#   #    |",
		"|         |       :         :       |         |",
		"|         |       :         :       |         |",
		"|                 :         :                 |",
		"|_____________________________________________|"}



	};

	memcpy(characterAvatar, avatars[0], (AVATARHEIGHT * AVATARLENGTH * sizeof(char)));
}

void lineUpBasedOnNumSize(int x)
{
	// makes column line up
	if (10 > x && x >= 0)
	{
		printf("    ");
	}
	else if (100 > x && x > -10)
	{
		printf("   ");
	}
	else if (1000 > x && x > -100)
	{
		printf("  ");
	}
	else if (10000 > x && x > -1000)
	{
		printf(" ");
	}
	else
	{
		printf("");
	}
}
