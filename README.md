# Projet_git_2425_ESE
Projet_2024/2025
## Membres du groupes
Bayazid BELKHIR
<br>
Hedia WERHENI
<br>
Hugo DEVAUX
<br>
Aliou LY

## Datasheets et sourcing des composants

https://1drv.ms/x/s!AjphXEW6glNckYErezblGW1QHlP9SQ

# Schema de cablage

https://www.canva.com/design/DAGQbxRenXI/GUDe0BMdF_tvJ-OYr82Fnw/edit?utm_content=DAGQbxRenXI&utm_campaign=designshare&utm_medium=link2&utm_source=sharebutton


# Infos Lidar

trame du YDLIDAR X4 se compose des éléments suivants :
<br>
- En-tête (2 octets) : Indique le début d'une nouvelle trame
- Longueur des données (1 octet) : Taille des données qui suivent
- Données de points (variable) : Informations sur chaque point mesuré
- Checksum (2 octets) : Pour vérifier l'intégrité des données
<br>
(Pour chaque point)

RQ: Utiliser un struct pour les données reçues


# Rappels git

## Les branches

### Creér une branche
``
git checkout -b <nom de la branche>
``

### Changer de branche
``
git checkout <nom de la branche>
``
 ## Commits et push
!!! ATTENTION À LA BRANCHE OÙ L'ON SE TROVUE !!!
```
git add . 
git commit -m "message de commit"
git push
```

## Merge dans le main
On utilise des PR (pull requests), on ne push jamais rien dans le `main`!
