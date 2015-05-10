///
// This file has been generated, if you wish to
// modify it in a permanent way, please refer
// to the script file : gen/generator_python.rb
//

#include "interface.hh"

static PyObject* c_module;
static PyObject* py_module;
static PyObject* champ_module;

static void _init_python();

template <typename Lang, typename Cxx>
Lang cxx2lang(Cxx in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
PyObject* cxx2lang<PyObject*, int>(int in)
{
  return PyLong_FromLong(in);
}


template <>
PyObject* cxx2lang<PyObject*, std::string>(std::string in)
{
return PyUnicode_FromString (in.c_str());
}


template <>
PyObject* cxx2lang<PyObject*, bool>(bool in)
{
  return PyBool_FromLong(in);
}

template <typename Cxx>
PyObject* cxx2lang_array(const std::vector<Cxx>& in)
{
  size_t size = in.size();
  PyObject* out = PyList_New(size);

  for (unsigned int i = 0; i < size; ++i)
    PyList_SET_ITEM(out, i, (cxx2lang<PyObject*, Cxx>(in[i])));

  return out;
}

template <typename Lang, typename Cxx>
Cxx lang2cxx(Lang in)
{
  return in.__if_that_triggers_an_error_there_is_a_problem;
}

template <>
int lang2cxx<PyObject*, int>(PyObject* in)
{
  long out = PyLong_AsLong(in);
  if (out == -1)
    if (PyErr_Occurred())
    {
      throw 42;
    }

  return out;
}

template <>
bool lang2cxx<PyObject*, bool>(PyObject* in)
{
  return (bool)lang2cxx<PyObject*, int>(in);
}

template <>
std::string lang2cxx<PyObject*, std::string>(PyObject* in)
{
  char * out = PyUnicode_AsUTF8(in);
  if (PyErr_Occurred())
    {
      throw 42;
    }
  return out;
}

template <typename Cxx>
std::vector<Cxx> lang2cxx_array(PyObject* in)
{
  if (!PyList_Check(in))
  {
    PyErr_SetString(PyExc_TypeError, "a list is required");
    throw 42;
  }

  std::vector<Cxx> out;
  unsigned int size = PyList_Size(in);

  for (unsigned int i = 0; i < size; ++i)
    out.push_back(lang2cxx<PyObject*, Cxx>(PyList_GET_ITEM(in, i)));

  return out;
}
///
// Erreurs possibles
//
template <>
PyObject* cxx2lang<PyObject*, erreur>(erreur in)
{
  PyObject* name = PyUnicode_FromString("erreur");
  PyObject* enm = PyObject_GetAttr(py_module, name);
  if (enm == NULL) throw 42;
  PyObject* arglist = Py_BuildValue("(i)", (int) in);
  PyObject* ret = PyObject_CallObject(enm, arglist);
  Py_DECREF(name);
  Py_DECREF(arglist);
  Py_DECREF(enm);
  return ret;
}

template <>
erreur lang2cxx<PyObject*, erreur>(PyObject* in)
{
  return (erreur)lang2cxx<PyObject*, int>(in);
}

///
// Position sur la carte, donnée par deux coordonnées.
//
template <>
PyObject* cxx2lang<PyObject*, position>(position in)
{
  PyObject* tuple = PyTuple_New(2);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, int>(in.x)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, int>(in.y)));
  return tuple;
}

template <>
position lang2cxx<PyObject*, position>(PyObject* in)
{
  position out;
  PyObject* i;
  i = PyTuple_GetItem(in, 0);
  if (i == NULL) throw 42;
  out.x = lang2cxx<PyObject*, int>(i);
  i = PyTuple_GetItem(in, 1);
  if (i == NULL) throw 42;
  out.y = lang2cxx<PyObject*, int>(i);
  return out;
}

///
// Représente un lien existant.
//
template <>
PyObject* cxx2lang<PyObject*, lien>(lien in)
{
  PyObject* tuple = PyTuple_New(3);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, position>(in.extr1)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, position>(in.extr2)));
  PyTuple_SET_ITEM(tuple, 2, (cxx2lang<PyObject*, int>(in.joueur_l)));
  PyObject* name = PyUnicode_FromString("lien");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
lien lang2cxx<PyObject*, lien>(PyObject* in)
{
  lien out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.extr1 = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.extr2 = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(2);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.joueur_l = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  return out;
}

///
// Représente un champ de contrôle existant.
//
template <>
PyObject* cxx2lang<PyObject*, champ>(champ in)
{
  PyObject* tuple = PyTuple_New(4);
  PyTuple_SET_ITEM(tuple, 0, (cxx2lang<PyObject*, position>(in.som1)));
  PyTuple_SET_ITEM(tuple, 1, (cxx2lang<PyObject*, position>(in.som2)));
  PyTuple_SET_ITEM(tuple, 2, (cxx2lang<PyObject*, position>(in.som3)));
  PyTuple_SET_ITEM(tuple, 3, (cxx2lang<PyObject*, int>(in.joueur_c)));
  PyObject* name = PyUnicode_FromString("champ");
  PyObject* cstr = PyObject_GetAttr(py_module, name);
  Py_DECREF(name);
  if (cstr == NULL) throw 42;
  PyObject* ret = PyObject_CallObject(cstr, tuple);
  Py_DECREF(cstr);
  Py_DECREF(tuple);
  if (ret == NULL) throw 42;
  return ret;
}

template <>
champ lang2cxx<PyObject*, champ>(PyObject* in)
{
  champ out;
  PyObject* i;
  i = cxx2lang<PyObject*, int>(0);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.som1 = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(1);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.som2 = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(2);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.som3 = lang2cxx<PyObject*, position>(i);
  Py_DECREF(i);
  i = cxx2lang<PyObject*, int>(3);
  i = PyObject_GetItem(in, i);
  if (i == NULL) throw 42;
  out.joueur_c = lang2cxx<PyObject*, int>(i);
  Py_DECREF(i);
  return out;
}

///
// Déplace votre agent sur la case passée en argument.
//
static PyObject* p_deplacer(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_deplacer(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Utilise un turbo.
//
static PyObject* p_utiliser_turbo(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_utiliser_turbo());
  } catch (...) { return NULL; }
}

///
// Capture le portail où est positionné votre agent.
//
static PyObject* p_capturer(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_capturer());
  } catch (...) { return NULL; }
}

///
// Crée un lien entre le portail où se trouve votre agent et le portail de destination donné en argument.
//
static PyObject* p_lier(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_lier(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Neutralise le portail où se trouve votre agent.
//
static PyObject* p_neutraliser(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_neutraliser());
  } catch (...) { return NULL; }
}

///
// Ajoute un bouclier au portail sur lequel se trouve votre agent.
//
static PyObject* p_ajouter_bouclier(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, erreur>(api_ajouter_bouclier());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les liens présents.
//
static PyObject* p_liste_liens(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liste_liens());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les champs de contrôle.
//
static PyObject* p_liste_champs(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liste_champs());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les portails de la carte.
//
static PyObject* p_liste_portails(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liste_portails());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les liens existants qui croisent un segment, entravant la création d'un lien.
//
static PyObject* p_liens_bloquants(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liens_bloquants(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Prend les positions de deux portails, et renvoie un booléen indiquant s'ils sont reliés. Le résultat est `false` lorsque l'une des deux positions ne repère pas un portail.
//
static PyObject* p_lien_existe(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_lien_existe(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Renvoie un booléen indiquant si les 3 positions repèrent bien 3 portails tous reliés entre eux.
//
static PyObject* p_champ_existe(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
  if (!PyArg_ParseTuple(args, "OOO", &a0, &a1, &a2)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_champ_existe(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1), lang2cxx<PyObject*, position>(a2)));
  } catch (...) { return NULL; }
}

///
// Renvoie un booléen indiquant si la case ``pos`` se trouve dans un champ.
//
static PyObject* p_case_dans_champ(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_case_dans_champ(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des champs à l'intérieur desquels ``pos`` se trouve. Si la case est un portail, le résultat de ``case_champs`` sera disjoint de celui de ``champs_incidents_portail``.
//
static PyObject* p_case_champs(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_case_champs(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie le numéro du joueur correspondant au portail donné, -1 si le portail est neutre, -2 si la case n'est pas un portail. Vous pouvez utiliser cette fonction pour vérifier qu'une case donnée est bien un portail.
//
static PyObject* p_portail_joueur(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_portail_joueur(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie le nombre de boucliers présents sur un portail (-2 si la case n'est pas un portail).
//
static PyObject* p_portail_boucliers(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_portail_boucliers(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les liens dont le portail donné est une extrémité.
//
static PyObject* p_liens_incidents_portail(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_liens_incidents_portail(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les champs dont le portail donné est un sommet.
//
static PyObject* p_champs_incidents_portail(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_champs_incidents_portail(lang2cxx<PyObject*, position>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie la liste de tous les champs dont le lien donné est un côté. Si le segment n'est pas un lien présent, renvoie la liste de tous les champs que la création du lien ferait apparaître.
//
static PyObject* p_champs_incidents_segment(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang_array(api_champs_incidents_segment(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des portails capturés par votre adversaire au dernier tour.
//
static PyObject* p_hist_portails_captures(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_hist_portails_captures());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des portails neutralisés par votre adversaire au dernier tour.
//
static PyObject* p_hist_portails_neutralises(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_hist_portails_neutralises());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des liens créés par votre adversaire au dernier tour.
//
static PyObject* p_hist_liens_crees(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_hist_liens_crees());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des champs créés par votre adversaire au dernier tour.
//
static PyObject* p_hist_champs_crees(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_hist_champs_crees());
  } catch (...) { return NULL; }
}

///
// Renvoie la liste des positions où votre adversaire a ajouté des boucliers au dernier tour.
//
static PyObject* p_hist_boucliers_ajoutes(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang_array(api_hist_boucliers_ajoutes());
  } catch (...) { return NULL; }
}

///
// Renvoie la distance de Manhattan entre deux positions.
//
static PyObject* p_distance(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
  if (!PyArg_ParseTuple(args, "OO", &a0, &a1)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_distance(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1)));
  } catch (...) { return NULL; }
}

///
// Renvoie le nombre de points que rapporte(rait) chaque tour un champ existant ou hypothétique.
//
static PyObject* p_score_triangle(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
  if (!PyArg_ParseTuple(args, "OOO", &a0, &a1, &a2)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_score_triangle(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1), lang2cxx<PyObject*, position>(a2)));
  } catch (...) { return NULL; }
}

///
// Indique si deux segments se croisent. Cette fonction correspond exactement à la condition d'interférence entre liens, c'est-à-dire qu'elle renvoie ``false`` si l'intersection est une extrémité des deux segments.
//
static PyObject* p_intersection_segments(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
PyObject* a3;
  if (!PyArg_ParseTuple(args, "OOOO", &a0, &a1, &a2, &a3)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_intersection_segments(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1), lang2cxx<PyObject*, position>(a2), lang2cxx<PyObject*, position>(a3)));
  } catch (...) { return NULL; }
}

///
// Indique si un point se trouve à l'intérieur d'un triangle. Le critère coïncide avec celui de ``case_champs``.
//
static PyObject* p_point_dans_triangle(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
PyObject* a1;
PyObject* a2;
PyObject* a3;
  if (!PyArg_ParseTuple(args, "OOOO", &a0, &a1, &a2, &a3)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_point_dans_triangle(lang2cxx<PyObject*, position>(a0), lang2cxx<PyObject*, position>(a1), lang2cxx<PyObject*, position>(a2), lang2cxx<PyObject*, position>(a3)));
  } catch (...) { return NULL; }
}

///
// Renvoie votre numéro de joueur.
//
static PyObject* p_moi(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_moi());
  } catch (...) { return NULL; }
}

///
// Renvoie le numéro de votre adversaire.
//
static PyObject* p_adversaire(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_adversaire());
  } catch (...) { return NULL; }
}

///
// Indique la position de l'agent du joueur désigné par le numéro ``id_joueur``.
//
static PyObject* p_position_agent(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, position>(api_position_agent(lang2cxx<PyObject*, int>(a0)));
  } catch (...) { return NULL; }
}

///
// Indique votre nombre de points d'actions restants pour ce tour-ci.
//
static PyObject* p_points_action(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_points_action());
  } catch (...) { return NULL; }
}

///
// Indique votre nombre de points de déplacement restants pour ce tour-ci.
//
static PyObject* p_points_deplacement(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_points_deplacement());
  } catch (...) { return NULL; }
}

///
// Renvoie le score du joueur désigné par le numéro ``id_joueur``.
//
static PyObject* p_score(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_score(lang2cxx<PyObject*, int>(a0)));
  } catch (...) { return NULL; }
}

///
// Renvoie le numéro du tour actuel.
//
static PyObject* p_tour_actuel(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, int>(api_tour_actuel());
  } catch (...) { return NULL; }
}

///
// Annule la dernière action. Renvoie ``false`` quand il n'y a pas d'action à annuler ce tour-ci.
//
static PyObject* p_annuler(PyObject* self, PyObject* args)
{
  (void)self;
  if (!PyArg_ParseTuple(args, "")) {
    return NULL;
  }
    try {
return cxx2lang<PyObject*, bool>(api_annuler());
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type erreur
//
static PyObject* p_afficher_erreur(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_erreur(lang2cxx<PyObject*, erreur>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type position
//
static PyObject* p_afficher_position(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_position(lang2cxx<PyObject*, position>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type lien
//
static PyObject* p_afficher_lien(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_lien(lang2cxx<PyObject*, lien>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}

///
// Affiche le contenu d'une valeur de type champ
//
static PyObject* p_afficher_champ(PyObject* self, PyObject* args)
{
  (void)self;
PyObject* a0;
  if (!PyArg_ParseTuple(args, "O", &a0)) {
    return NULL;
  }
    try {
api_afficher_champ(lang2cxx<PyObject*, champ>(a0));
  Py_INCREF(Py_None);
  return Py_None;
  } catch (...) { return NULL; }
}


/*
** Api functions to register.
*/
static PyMethodDef api_callback[] = {
  {"deplacer", p_deplacer, METH_VARARGS, "deplacer"},  {"utiliser_turbo", p_utiliser_turbo, METH_VARARGS, "utiliser_turbo"},  {"capturer", p_capturer, METH_VARARGS, "capturer"},  {"lier", p_lier, METH_VARARGS, "lier"},  {"neutraliser", p_neutraliser, METH_VARARGS, "neutraliser"},  {"ajouter_bouclier", p_ajouter_bouclier, METH_VARARGS, "ajouter_bouclier"},  {"liste_liens", p_liste_liens, METH_VARARGS, "liste_liens"},  {"liste_champs", p_liste_champs, METH_VARARGS, "liste_champs"},  {"liste_portails", p_liste_portails, METH_VARARGS, "liste_portails"},  {"liens_bloquants", p_liens_bloquants, METH_VARARGS, "liens_bloquants"},  {"lien_existe", p_lien_existe, METH_VARARGS, "lien_existe"},  {"champ_existe", p_champ_existe, METH_VARARGS, "champ_existe"},  {"case_dans_champ", p_case_dans_champ, METH_VARARGS, "case_dans_champ"},  {"case_champs", p_case_champs, METH_VARARGS, "case_champs"},  {"portail_joueur", p_portail_joueur, METH_VARARGS, "portail_joueur"},  {"portail_boucliers", p_portail_boucliers, METH_VARARGS, "portail_boucliers"},  {"liens_incidents_portail", p_liens_incidents_portail, METH_VARARGS, "liens_incidents_portail"},  {"champs_incidents_portail", p_champs_incidents_portail, METH_VARARGS, "champs_incidents_portail"},  {"champs_incidents_segment", p_champs_incidents_segment, METH_VARARGS, "champs_incidents_segment"},  {"hist_portails_captures", p_hist_portails_captures, METH_VARARGS, "hist_portails_captures"},  {"hist_portails_neutralises", p_hist_portails_neutralises, METH_VARARGS, "hist_portails_neutralises"},  {"hist_liens_crees", p_hist_liens_crees, METH_VARARGS, "hist_liens_crees"},  {"hist_champs_crees", p_hist_champs_crees, METH_VARARGS, "hist_champs_crees"},  {"hist_boucliers_ajoutes", p_hist_boucliers_ajoutes, METH_VARARGS, "hist_boucliers_ajoutes"},  {"distance", p_distance, METH_VARARGS, "distance"},  {"score_triangle", p_score_triangle, METH_VARARGS, "score_triangle"},  {"intersection_segments", p_intersection_segments, METH_VARARGS, "intersection_segments"},  {"point_dans_triangle", p_point_dans_triangle, METH_VARARGS, "point_dans_triangle"},  {"moi", p_moi, METH_VARARGS, "moi"},  {"adversaire", p_adversaire, METH_VARARGS, "adversaire"},  {"position_agent", p_position_agent, METH_VARARGS, "position_agent"},  {"points_action", p_points_action, METH_VARARGS, "points_action"},  {"points_deplacement", p_points_deplacement, METH_VARARGS, "points_deplacement"},  {"score", p_score, METH_VARARGS, "score"},  {"tour_actuel", p_tour_actuel, METH_VARARGS, "tour_actuel"},  {"annuler", p_annuler, METH_VARARGS, "annuler"},  {"afficher_erreur", p_afficher_erreur, METH_VARARGS, "afficher_erreur"},  {"afficher_position", p_afficher_position, METH_VARARGS, "afficher_position"},  {"afficher_lien", p_afficher_lien, METH_VARARGS, "afficher_lien"},  {"afficher_champ", p_afficher_champ, METH_VARARGS, "afficher_champ"},  {NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC PyInit__api()
{
  static struct PyModuleDef apimoduledef = {
      PyModuleDef_HEAD_INIT,
      "_api",
      "API module",
      -1,
      api_callback,
      NULL,
      NULL,
      NULL,
      NULL,
  };
  return PyModule_Create(&apimoduledef);
}


/*
** Load a Python module
*/

static PyObject* _import_module(const char* m)
{
  PyObject* name = PyUnicode_FromString(m);
  PyObject* module = PyImport_Import(name);
  Py_DECREF(name);
  if (module == NULL)
    if (PyErr_Occurred())
    {
      PyErr_Print();
      abort();
    }
  return module;
}

/*
** Inititialize python, register API functions,
** and load .py file
*/
static void _init_python()
{
  static wchar_t empty_string[] = L"";
  static wchar_t *argv[] = { (wchar_t *) &empty_string, NULL };

  const char* champion_path;

  champion_path = getenv("CHAMPION_PATH");
  if (champion_path == NULL)
    champion_path = ".";

  setenv("PYTHONPATH", champion_path, 1);

  static wchar_t program_name[] = L"stechec";
  Py_SetProgramName(program_name);

  PyImport_AppendInittab("_api", PyInit__api);
  Py_Initialize();
  PySys_SetArgvEx(1, argv, 0);

  champ_module = _import_module("prologin");
  py_module = _import_module("api");
}

/*
** Run a python function.
*/
static PyObject* _call_python_function(const char* name)
{
  static bool initialized = false;

  if (!initialized)
  {
    initialized = true;
    _init_python();
  }

  PyObject *arglist, *func;
  PyObject *result = NULL;

  func = PyObject_GetAttrString(champ_module, (char*)name);
  if (func && PyCallable_Check(func))
  {
    arglist = Py_BuildValue("()");
    result = PyEval_CallObject(func, arglist);
    Py_XDECREF(arglist);
    Py_DECREF(func);
  }
  if (result == NULL && PyErr_Occurred())
    PyErr_Print();

  return result;
}

/*
** Functions called from stechec to C.
*/
extern "C" void partie_init()
{
  PyObject* _retval = _call_python_function("partie_init");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void jouer_tour()
{
  PyObject* _retval = _call_python_function("jouer_tour");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

extern "C" void partie_fin()
{
  PyObject* _retval = _call_python_function("partie_fin");
  if (!_retval && PyErr_Occurred()) { PyErr_Print(); abort(); }
  try {
  Py_XDECREF(_retval);
  } catch (...) { PyErr_Print(); abort(); }
}

