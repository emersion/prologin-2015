from api import *
import random

DEBUG = 3

# Display

def msg_header(msg_type, flags=""):
	return "[#"+str(tour_actuel())+"]["+str(moi())+"]"+flags+" "+msg_type+": "

def print_msg(*kargs):
	if DEBUG < 1:
		return
	print(*kargs)

def warn(err, category=""):
	if category != "":
		category = "["+category+"]"
	print_msg(msg_header("WARN", category), err)

def info(msg, category=""):
	if DEBUG < 2:
		return
	if category != "":
		category = "["+category+"]"
	print_msg(msg_header("INFO", category), msg)

def debug(msg, category=""):
	if DEBUG < 3:
		return
	if category != "":
		category = "["+category+"]"
	print_msg(msg_header("DEBUG", category), msg)

def welcome():
	# Best feature EVER
	msgs = [
		"Gloire a Schroder !",
		"Que le champion le plus champion gagne !",
		"Je suis un psychopathe, je mange des pates",
		"Jouj ! Bienvenue a Praulojain !",
		"De quel agrume ?",
		"Que la sauce commence !",
		"Appelle vite tes curlis... Avant que je te desaas !",
		"Que Schroder te pardonne pour tes peches !"
	]
	welcome_msg = random.sample(msgs, 1)[0]
	print(msg_header("WELCOME"), welcome_msg)

# Others

def compare_pos(a, b):
	return a[0] == b[0] and a[1] == b[0]

def map_density():
	pass

def portals_by_player(player): # TODO: yield
	portals = []
	for p in liste_portails():
		if portail_joueur(p) == player:
			portals.append(p)
	return portals

def unowned_portals():
	portals = []
	for p in liste_portails():
		if portail_joueur(p) != moi():
			portals.append(p)
	return portals

def nearest(positions):
	from_pos = position_agent(moi())
	nearest = None
	nearest_dist = None
	for p in positions:
		dist = distance(from_pos, p)
		if nearest is None or nearest_dist > dist:
			nearest = p
			nearest_dist = dist
	return nearest

def links_mean_length(links):
	if len(links) == 0:
		return 0

	dist = 0
	for l in links:
		dist += distance(l[0], l[1])
	return dist / len(links)

def new_links(pos):
	if case_dans_champ(pos):
		return []

	links = []
	for p in liste_portails():
		owner = portail_joueur(p)
		if p == pos:
			continue
		if owner != moi():
			continue
		if lien_existe(pos, p):
			continue
		if case_dans_champ(p):
			continue
		
		blocking = liens_bloquants(pos, p)
		if owner == adversaire():
			blocking_count = 0
			for l in blocking:
				if compare_pos(l[0], pos) or compare_pos(l[1], pos):
					continue
				blocking_count += 1
				break
			if blocking_count > 0: # TODO: destroy these links first?
				continue
		else:
			if len(blocking) > 0:
				continue

		links.append((pos, p))
	return links

def new_links_sorted(pos):
	links = new_links(pos)
	links.sort(reverse=True, key=lambda l: distance(l[0], l[1]))
	return links

def new_links_count(pos):
	return len(new_links(pos))

def new_links_dist(pos):
	dist = 0
	for l in new_links(pos):
		dist += distance(l[0], l[1])
	return dist

def new_links_mean_dist(pos):
	return links_mean_length(new_links(pos))

def new_links_area(pos):
	pass # TODO: unimplemented

def target_cost(t):
	cost = 0

	owner = portail_joueur(t)
	if owner == adversaire():
		cost += COUT_NEUTRALISATION
		cost += COUT_NEUTRALISATION_BOUCLIER * portail_boucliers(t)

	return cost

def portal_score(pos):
	score = 0

	links = liens_incidents_portail(pos)
	for l1 in links:
		for l2 in links:
			a = l1[0]
			if a == pos:
				a = l1[1]
			b = l2[0]
			if b == pos:
				b = l2[1]

			if not lien_existe(a, b):
				continue

			score += score_triangle(a, b, pos)

	return score