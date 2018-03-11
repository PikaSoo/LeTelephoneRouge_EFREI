Il était une fois et ils vécurent heureux… toutes les histoires devraient commencer et finir comme ça,
un avant-goût prometteur de bons évènements, d’une belle fin faite de joyeux sentiments,
de câlins et de bisounours à vous en faire chier des arcs-en-ciel. 

Sauf que non, on n’est pas dans ce monde-là.
 
Ici, rien de glorieux, une lutte sans merci pour la survie,
un besoin irrépressible de voir l’aube de nouveau et libre de préférence,
ainsi sont les prisonniers du Goulag.
Quand ils commencent à prendre les choses en mains, leur silhouette minuscule se dresse,
fière et vaillante sous les hurlements des détenus en hauteur,
les lumières dansent autour d'eux et les éblouissent mais ils poursuivent leur combat,
petits hommes rêvant d’un nouvel air, parcourant l’arène et laissant derrière eux un chemin de lumière.

Il parait que le jeu en vaut la chandelle, c’est ce qu’ils disent tous,
avant de se jeter dans l’arène. Jamais un seul n’est revenu.
Après tout, quand tu gagnes, tu es libre alors pourquoi rester. Prêt à jouer, petit prisonnier ?

______________________________

Règles du jeu:

Vous avancez d’une case tour par tour, dans une map carré de largeur sqrt(120*NOMBRE_DE_JOUEURS). 
A chaque déplacement vous laissez une trainée sur votre ancienne position.

•	Si une ia passe par une case où se trouve une autre ia, l'ia qui as effectué le déplacement meurt.

•	Si une ia passe par une case où se trouve une trainée, l’ia perd automatiquement.

•	Une ia perd lorsqu’elle revient sur son emplacement précédent. 

•	L’ia peut se déplacer sur le mur mais ne peut pas le traverser, sinon elle perd.

•	Votre ia ne n’apparaitra jamais sur un mur.

•	Pour gagner, soyez le dernier en vie, pour cela, faite adopter à votre ia une stratégie de survie.
 
 ______________________________
 
 Doc technique :
 
 Le prototype de la fonction ia est le suivant :
 
 int* ia(int** pMat,int* last,int* dep);
 
 pMat --> Matrice contenant un entier pour chaque case de l'arène de jeu. L'entier de chaque case correspond à son état.
          Si l'entier est <= 0, c'est une case libre. Si l'entier est > 0 , c'est une case dite "occupée",
          si votre ia se déplace dessus, elle perd. NE DOIS PAS ÊTRE MODIFIEE.
          
 last --> Tableau contenant la dernière position de votre ia. last = {x,y}. NE DOIS PAS ÊTRE MODIFIEE.
 
 dep --> Pointeur sur entier, utilisez le pour renvoyer la direction choisie par votre ia. 
         1: TOP
         2: RIGHT
         3: BOTTOM
         4: LEFT

 ______________________________
 
 Arène "Le Téléphone Rouge" par URSS & RyanSoGui.
 Paul BOULOC
 Florian BRUNET
 Hadrien BASSERY
 Sonia LEYRIS
 Guillaume POIGNANT
 Ryan VIEHWEGER
