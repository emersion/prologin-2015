# -*- coding: iso-8859-1 -*-
from _api import *

# Taille du terrain (longueur et largeur).
TAILLE_TERRAIN = 30

# Nombre de tours à jouer avant la fin de la partie.
NB_TOURS = 100

# Nombre de points de déplacement par tour (avant utilisation du turbo).
NB_POINTS_DEPLACEMENT = 6

# Nombre de points d'action par tour.
NB_POINTS_ACTION = 42

# Nombre de points d'action que coûte la capture d'un portail.
COUT_CAPTURE = 3

# Nombre de points d'action que coûte la création d'un lien.
COUT_LIEN = 2

# Nombre de points d'action que coûte la neutralisation d'un portail de base.
COUT_NEUTRALISATION = 10

# Nombre de points d'action supplémentaires que coûte la neutralisation pour chaque bouclier présent.
COUT_NEUTRALISATION_BOUCLIER = 5

# Nombre de points d'action que coûte la mise en place d'un bouclier sur un portail sans bouclier.
COUT_BOUCLIER = 3

# Nombre de points d'action que coûte l'utilisation d'un turbo.
COUT_TURBO = 6

# Nombre maximum de boucliers sur un même portail.
MAX_BOUCLIERS = 6

# Nombre de points que rapporte la capture d'un portail.
POINTS_CAPTURE = 10

# Constante de proportionnalité reliant l'aire d'un champ au nombre de points qu'il rapporte par tour.
POINTS_CHAMP = 2


from enum import IntEnum

# Erreurs possibles
class erreur(IntEnum):
    OK = 0  # <- L'action a été exécutée avec succès
    PA_INSUFFISANTS = 1  # <- Vous ne possédez pas assez de points d'action pour cette action.
    AUCUN_PORTAIL = 2  # <- La position spécifiée n'est pas un portail.
    POSITION_INVALIDE = 3  # <- La position spécifiée est hors de la carte.
    POSITION_ELOIGNEE = 4  # <- La destination est trop éloignée.
    PORTAIL_AMI = 5  # <- Le portail vous appartient.
    PORTAIL_NEUTRE = 6  # <- Le portail est neutre.
    PORTAIL_ENNEMI = 7  # <- Le portail appartient à votre adversaire.
    LIEN_INTERSECTION = 8  # <- Le lien croise un lien existant.
    LIEN_CHAMP = 9  # <- Le lien se trouve dans un champ existant.
    LIEN_DEGENERE = 10  # <- Les deux extrémités du lien coïncident.
    LIMITE_BOUCLIERS = 11  # <- Ce portail est équipé du nombre maximal de boucliers.


from collections import namedtuple

# Position sur la carte, donnée par deux coordonnées.

# Représente un lien existant.
lien = namedtuple("lien",
    'extr1 ' # <- Première extrémité du lien.
    'extr2 ' # <- Seconde extrémité du lien.
    'joueur_l ' # <- Joueur possédant ce lien.
)


# Représente un champ de contrôle existant.
champ = namedtuple("champ",
    'som1 ' # <- Premier sommet du champ.
    'som2 ' # <- Deuxième sommet du champ.
    'som3 ' # <- Troisième sommet du champ.
    'joueur_c ' # <- Joueur possédant ce champ.
)


