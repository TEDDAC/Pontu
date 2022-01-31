# Pontu
#### Algorithme de la boucle main

Voici l'algorithme gérant les vue et les liens entre elles
```
etat = menu principal

tant que etat différent de quit, faire
    switch etat
        case MainMenu   //code similaire pour chaque menu, seul la boucle change, mais elle peut être encapsulé dans une fonction
            afficher MainMenu
            tant que vrai
                si bouton cliqué
                    si bouton = option bouton
                        tant que
                            ... //code de la fenêtre d'option
                    si bouton = quit
                        etat = quit
                        break;
        case CreationGameMenu
            ...
    fin switch
```
