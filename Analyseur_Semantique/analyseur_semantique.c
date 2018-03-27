#include "analyseur_semantique.h"

void parcours_n_prog(n_prog *n);
void parcours_l_instr(n_l_instr *n);
void parcours_instr(n_instr *n);
void parcours_instr_si(n_instr *n);
void parcours_instr_tantque(n_instr *n);
void parcours_instr_affect(n_instr *n);
void parcours_instr_appel(n_instr *n);
void parcours_instr_retour(n_instr *n);
void parcours_instr_ecrire(n_instr *n);
int parcours_l_exp(n_l_exp *n, int nb_exp);
void parcours_exp(n_exp *n);
void parcours_varExp(n_exp *n);
void parcours_opExp(n_exp *n);
void parcours_intExp(n_exp *n);
void parcours_lireExp(n_exp *n);
void parcours_appelExp(n_exp *n);
int parcours_l_dec(n_l_dec *n, int nb_arg);
void parcours_dec(n_dec *n);
void parcours_foncDec(n_dec *n);
void parcours_varDec(n_dec *n);
void parcours_tabDec(n_dec *n);
void parcours_var(n_var *n);
void parcours_var_simple(n_var *n);
void parcours_var_indicee(n_var *n);
void parcours_appel(n_appel *n);

//int trace_abs = 1; Already defined in affiche_arbre_abstrait

/*-------------------------------------------------------------------------*/

void parcours_n_prog(n_prog *n)
{
  portee = P_VARIABLE_GLOBALE;
  adresseGlobaleCourante = 0;
  parcours_l_dec(n->variables, 0);
  parcours_l_dec(n->fonctions, 0);

  if(rechercheExecutable("main") == -1){
    erreur("La fonction main n'a pas ete declaree\n");
  }

}

/*-------------------------------------------------------------------------*/
/*-------------------------------------------------------------------------*/

void parcours_l_instr(n_l_instr *n)
{
  if(n){
    parcours_instr(n->tete);
    parcours_l_instr(n->queue);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr(n_instr *n)
{
  if(n){
    if(n->type == blocInst) parcours_l_instr(n->u.liste);
    else if(n->type == affecteInst) parcours_instr_affect(n);
    else if(n->type == siInst) parcours_instr_si(n);
    else if(n->type == tantqueInst) parcours_instr_tantque(n);
    else if(n->type == appelInst) parcours_instr_appel(n);
    else if(n->type == retourInst) parcours_instr_retour(n);
    else if(n->type == ecrireInst) parcours_instr_ecrire(n);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_si(n_instr *n)
{
  parcours_exp(n->u.si_.test);
  parcours_instr(n->u.si_.alors);
  if(n->u.si_.sinon){
    parcours_instr(n->u.si_.sinon);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_instr_tantque(n_instr *n)
{
  parcours_exp(n->u.tantque_.test);
  parcours_instr(n->u.tantque_.faire);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_affect(n_instr *n)
{
  parcours_var(n->u.affecte_.var);
  parcours_exp(n->u.affecte_.exp);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_appel(n_instr *n)
{
  parcours_appel(n->u.appel);
}
/*-------------------------------------------------------------------------*/

void parcours_appel(n_appel *n)
{
  /*char *fct = "appel";
  parcours_balise_ouvrante(fct, trace_abs);
  parcours_texte( n->fonction, trace_abs);
  parcours_l_exp(n->args);
  parcours_balise_fermante(fct, trace_abs);*/

  int test = rechercheExecutable(n->fonction);

  if(test == -1){
    erreur("Cette fonction n a pas ete declaree\n");
  }
  int nb_exp = parcours_l_exp(n->args, 0);

  if(tabsymboles.tab[test].complement != nb_exp){
    erreur("L appel de fonction ne comporte pas le meme nombre de parametre que la declaration\n");
  }

}

/*-------------------------------------------------------------------------*/

void parcours_instr_retour(n_instr *n)
{
  parcours_exp(n->u.retour_.expression);
}

/*-------------------------------------------------------------------------*/

void parcours_instr_ecrire(n_instr *n)
{
  parcours_exp(n->u.ecrire_.expression);
}

/*-------------------------------------------------------------------------*/

int parcours_l_exp(n_l_exp *n, int nb_exp)
{
  if(n){
    parcours_exp(n->tete);
    return parcours_l_exp(n->queue, nb_exp + 1);
  }

  return nb_exp;
}

/*-------------------------------------------------------------------------*/

void parcours_exp(n_exp *n)
{

  if(n->type == varExp) parcours_varExp(n);
  else if(n->type == opExp) parcours_opExp(n);
  else if(n->type == intExp) parcours_intExp(n);
  else if(n->type == appelExp) parcours_appelExp(n);
  else if(n->type == lireExp) parcours_lireExp(n);
}

/*-------------------------------------------------------------------------*/

void parcours_varExp(n_exp *n)
{
  parcours_var(n->u.var);
}

/*-------------------------------------------------------------------------*/
void parcours_opExp(n_exp *n)
{
  /*if(n->u.opExp_.op == plus) parcours_texte("plus", trace_abs);
  else if(n->u.opExp_.op == moins) parcours_texte("moins", trace_abs);
  else if(n->u.opExp_.op == fois) parcours_texte("fois", trace_abs);
  else if(n->u.opExp_.op == divise) parcours_texte("divise", trace_abs);
  else if(n->u.opExp_.op == egal) parcours_texte("egal", trace_abs);
  else if(n->u.opExp_.op == inferieur) parcours_texte("inf", trace_abs);
  else if(n->u.opExp_.op == ou) parcours_texte("ou", trace_abs);
  else if(n->u.opExp_.op == et) parcours_texte("et", trace_abs);
  else if(n->u.opExp_.op == non) parcours_texte("non", trace_abs);*/

  if( n->u.opExp_.op1 != NULL) {
    parcours_exp(n->u.opExp_.op1);
  }
  if( n->u.opExp_.op2 != NULL) {
    parcours_exp(n->u.opExp_.op2);
  }
}

/*-------------------------------------------------------------------------*/

void parcours_intExp(n_exp *n)
{
  /*char texte[ 50 ];
  sprintf(texte, "%d", n->u.entier);*/
}

/*-------------------------------------------------------------------------*/
void parcours_lireExp(n_exp *n)
{

}

/*-------------------------------------------------------------------------*/

void parcours_appelExp(n_exp *n)
{
  parcours_appel(n->u.appel);
}

/*-------------------------------------------------------------------------*/

int parcours_l_dec(n_l_dec *n, int nb_arg)
{
  if( n ){
    parcours_dec(n->tete);
    return parcours_l_dec(n->queue, nb_arg + 1);
  }

  return nb_arg;
}

/*-------------------------------------------------------------------------*/

void parcours_dec(n_dec *n)
{

  if(n){
    if(n->type == foncDec) {
      parcours_foncDec(n);
    }
    else if(n->type == varDec) {
      parcours_varDec(n);
    }
    else if(n->type == tabDec) { 
      parcours_tabDec(n);
    }
  }
}

/*-------------------------------------------------------------------------*/

void parcours_foncDec(n_dec *n)
{
  if(!strcmp(n->nom,"lire") || !strcmp(n->nom,"ecrire")){
    erreur("Une fonction avec le nom lire ou ecrire ne peut etre declare\n");
  }
  //Test si une fonction du meme nom n existe pas deja
  int test = rechercheDeclarative(n->nom);

  if(test != -1){
    erreur("Une fonction du meme nom existe deja\n");
  }

  //On ajoute la fonction a la table des symboles
  int foncLine = ajouteIdentificateur(n->nom, P_VARIABLE_GLOBALE, T_FONCTION, 0, 0);

  entreeFonction();
  //On est oblige pour l instant de rechercher la fonction comme si elle etait utilise pour la retrouver
  //dans le scope global depuis le scope local
  tabsymboles.tab[foncLine].complement = parcours_l_dec(n->u.foncDec_.param, 0);

  //Si la fonction main a des arguments
  if(strcmp(n->nom,"main") == 0 && tabsymboles.tab[foncLine].complement != 0){
    erreur("La fonction main ne doit pas prendre d arguments\n");
  }
  //On passe en scope local
  portee = P_VARIABLE_LOCALE;
  parcours_l_dec(n->u.foncDec_.variables, 0);
  parcours_instr(n->u.foncDec_.corps);
  
  sortieFonction(1);
}

/*-------------------------------------------------------------------------*/

void parcours_varDec(n_dec *n)
{
  int test = rechercheDeclarative(n->nom);

  //Test si deux variables ont la meme portee
  if(test != -1 && tabsymboles.tab[test].portee == portee){
    erreur("Deux variable de meme nom dans la meme portee est impossible\n");
  }

  //Test si si une variable locale a le meme nom qu un argumen
  if(test != -1 && tabsymboles.tab[test].portee == P_ARGUMENT && portee == P_VARIABLE_LOCALE){
    erreur("Une variable locale ne peut avoir le meme nom qu un argument\n");
  }
  if(portee == P_VARIABLE_GLOBALE){
    ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseGlobaleCourante, 1);
    adresseGlobaleCourante += 4;
  }else if(portee == P_ARGUMENT){
    ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseArgumentCourant, 1);
    adresseArgumentCourant += 4;
  }else{
    ajouteIdentificateur(n->nom, portee, T_ENTIER, adresseLocaleCourante, 1);
    adresseLocaleCourante += 4;
  }
}

/*-------------------------------------------------------------------------*/

void parcours_tabDec(n_dec *n)
{
  int test = rechercheDeclarative(n->nom);

  if(portee != P_VARIABLE_GLOBALE){
    erreur("Un tableau ne peut que etre declare dans le scope global\n");
  }

  if(test != -1){
    erreur("Un tableau de meme nom a deja ete declare\n");
  }

  ajouteIdentificateur(n->nom, portee, T_TABLEAU_ENTIER, adresseGlobaleCourante, n->u.tabDec_.taille);
  adresseGlobaleCourante += n->u.tabDec_.taille * 4;
}

/*-------------------------------------------------------------------------*/

void parcours_var(n_var *n)
{
  if(n->type == simple) {
    parcours_var_simple(n);
  }
  else if(n->type == indicee) {
    parcours_var_indicee(n);
  }
}

/*-------------------------------------------------------------------------*/
void parcours_var_simple(n_var *n)
{
  int test = rechercheExecutable(n->nom);

  if(test == -1){
    erreur("La variable n a pas ete declare\n");
  }

  if(tabsymboles.tab[test].type != T_ENTIER){
    erreur("Un tableau a peut etre ete utilise sans indice\n");
  }
}

/*-------------------------------------------------------------------------*/
void parcours_var_indicee(n_var *n)
{
  int test = rechercheExecutable(n->nom);

  if(test == -1){
    erreur("La variable n a pas ete declare\n");
  }

  if(tabsymboles.tab[test].type != T_TABLEAU_ENTIER){
    erreur("Une variable a peut etre ete utilisee avec un indice\n");
  }

  parcours_exp( n->u.indicee_.indice );
}
/*-------------------------------------------------------------------------*/
