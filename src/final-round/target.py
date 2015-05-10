from api import *
from utils import *

agent = None
history = None
def set_ctx(a, h):
	global agent
	global history

	agent = a
	history = h

def filter_portals(portals):
	from_pos = position_agent(moi())

	portals.sort(key=lambda p: abs(NB_POINTS_DEPLACEMENT-distance(from_pos, p)))

	return portals[:35]

def score(p):
	global agent
	global history

	from_pos = position_agent(moi())
	dist = distance(from_pos, p)
	owner = portail_joueur(p)

	if dist == 0:
		return
	if case_dans_champ(p): # TODO: try to destroy field?
		return
	if history.was_target_cyclic(p):
		return

	score = []
	score.append((TAILLE_TERRAIN**2 - dist) * 100 * 1.15)

	possible_links = new_links(p)

	if owner == -1 or owner == adversaire():
		score.append(100)

		if len(possible_links) > 0:
			for l1 in possible_links:
				a = l1[1]
				for l2 in possible_links:
					b = l2[1]
					if not lien_existe(a, b):
						continue
					score.append(score_triangle(p, a, b))

	if owner == -1:
		pass #score.append(links_mean_length(possible_links) * 5)

	if owner == adversaire():
		#shields = portail_boucliers(p)
		current_links = liens_incidents_portail(p)
		score.append(len(current_links) * 10)

		if len(current_links) > 3:
			score.append(links_mean_length(current_links) * 25)

		#score.append(links_mean_length(possible_links) * 5)
		score.append(portal_score(p))

	if owner == moi():
		if len(possible_links) == 0:
			return
		score.append(links_mean_length(possible_links) * 5)

	dst_to_center = ((TAILLE_TERRAIN/2-p[0])**2 + (TAILLE_TERRAIN/2-p[1])**2)**0.5
	score.append(dst_to_center * 5)

	if agent.target == p:
		score.append(50)
		if agent.remaining_dist == 0:
			score.append(150)

	return sum(score)

def find(blacklist=None):
	best = None
	best_score = 0
	portals = liste_portails()

	if len(portals) > 100:
		portals = filter_portals(portals)

	for p in portals:
		if blacklist is not None:
			if blacklist == p or p in blacklist:
				#info("Blacklisted "+repr(p)+" portal ignored", "Target.find")
				continue

		s = score(p)

		if s is None:
			continue

		if s > best_score:
			best = p
			best_score = s

	#print("LINKS", new_links(best))
	return best