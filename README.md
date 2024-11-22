# Compte rendu Workshop Programmation Alice JACQUES
- [Compte rendu Workshop Programmation Alice JACQUES](#compte-rendu-workshop-programmation-alice-jacques)
  - [Introduction](#introduction)
  - [Exercices avec l'image logo.png](#exercices-avec-limage-logopng)
    - [Ne garder que le vert ⭐](#ne-garder-que-le-vert-)
    - [Échanger les canaux ⭐](#échanger-les-canaux-)
    - [Noir \& Blanc ⭐](#noir--blanc-)
    - [Négatif ⭐](#négatif-)
    - [Miroir ⭐⭐](#miroir-)
    - [Image bruitée ⭐⭐](#image-bruitée-)
    - [Rotation de 90° ⭐⭐](#rotation-de-90-)
    - [RGB Split ⭐⭐](#rgb-split-)
    - [Mosaïque ⭐⭐](#mosaïque-)
    - [Mosaïque miroir ⭐⭐⭐⭐](#mosaïque-miroir-)
    - [Glitch ⭐⭐⭐](#glitch-)
    - [Tri de pixels ⭐⭐⭐](#tri-de-pixels-)
    - [Vortex ⭐⭐⭐⭐](#vortex-)
  - [Exercices avec l'image photo.jpg](#exercices-avec-limage-photojpg)
    - [Luminosité ⭐⭐](#luminosité-)
      - [Eclaircissement](#eclaircissement)
      - [Assombrissement](#assombrissement)
    - [Tramage ⭐⭐⭐(⭐)](#tramage-)
    - [Normalisation de l'histogramme ⭐⭐⭐(⭐)](#normalisation-de-lhistogramme-)
  - [Exercices à partir de rien (pas d'images de base)](#exercices-à-partir-de-rien-pas-dimages-de-base)
    - [Dégradé ⭐](#dégradé-)
    - [Disque ⭐⭐(⭐)](#disque-)
    - [Cercle ⭐](#cercle-)
    - [Animation ⭐⭐](#animation-)
    - [Rosace ⭐⭐⭐](#rosace-)
    - [Fractale de Mandelbrot](#fractale-de-mandelbrot)
  - [Quelques ratés](#quelques-ratés)


## Introduction
Voici mon compte rendu de la semaine workshop. L'objectif a été d'apprendre à coder des effets sur des images.

## Exercices avec l'image logo.png
Voici les exercices réalisés avec l'image de base suivante : 

![logo.png](/images/logo.png)
### Ne garder que le vert ⭐
L'objectif est de **garder seulement la couleur verte de l'image.** Pour ce faire, il faut mettre le rouge et le bleu à 0.

*A noter que pour (presque) chaque exercice, l'idée est de **parcourir l'ensemble des pixels de l'image grâce aux deux boucles** `for` ci-dessous.

```cpp
void green_only(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {
            image.pixel(x, y).r = 0;
            image.pixel(x, y).b = 0;
        }
    }
}
```
**Résultat final :**

![green_only](/output/green_only.png)


### Échanger les canaux ⭐

L'idée a été **d'échanger les canaux de deux couleurs**, ici le rouge et le bleu. Pour ce faire, j'ai utilisé :
```cpp 
std::swap(image.pixel(x, y).r, image.pixel(x, y).b);
``` 
Ce bout de code est situé au sein des boucles `for` parcourant les pixels de l'image.

**Résultat final :**

![channels_swap.png](/output/channels_swap.png)


### Noir & Blanc ⭐
Ici, nous cherchons à transformer l'image en **noir et blanc**. Pour se faire, il faut d'abord accéder à la **manipulation des pixels** de cette manière : 
```cpp
glm::vec3 &pixel = image.pixel(x, y);
```

Puis faire une **conversion en niveau de gris** grâce à :


```cpp
float gray = 0.21 * pixel.r + 0.72 * pixel.g + 0.07 * pixel.b;
```
Et enfin **l'application de la valeur grise** aux pixels rgb :

```cpp
pixel.r = gray;
pixel.g = gray;
pixel.b = gray;
```

**Résultat final :**

![black_white.png](/output/black_white.png)


### Négatif ⭐
Chaque composante du pixel est **remplacée par sa valeur complémentaire.** Pour ce faire, **on soustrait à 1 la valeur actuelle de la composante.**



**Exemple** : Si pixel.r représente l'intensité du rouge entre 0 et 1, sa nouvelle valeur sera `1.0f - pixel.r`
De même pour pixel.g (vert) et pixel.b (bleu) :

```cpp
pixel.r = 1.0f - pixel.r;
pixel.g = 1.0f - pixel.g;
pixel.b = 1.0f - pixel.b;
```
**Résultat final :**

![negative.png](/output/negative.png)


### Miroir ⭐⭐

Pour chaque pixel (x, y) dans la moitié gauche de l'image, on échange sa position avec le pixel correspondant dans la moitié droite de la même ligne. Le pixel à la position (x, y) est échangé avec le pixel à la position `(image.width() - (x + 1), y)`.

On utilise la fonction standard `std::swap` pour intervertir les deux pixels :

```cpp
std::swap(image.pixel(x, y), image.pixel(image.width() - (x + 1), y));
```
**Résultat final :**

![mirror.png](/output/mirror.png)

### Image bruitée ⭐⭐

Pour cet exercice, on utilise les probabilités pour modifier ou non un pixel en y ajoutant du bruit. 

La fonction `true_with_probability(0.2f)` retourne **true** dans **20 % des cas** (probabilité de 0.2).

Si c'est true, **le pixel est sélectionné pour être modifié.**
- Ses composantes rouge, verte et bleue sont assignées à **une valeur aléatoire entre 0 et 1**.
- La fonction `random_float(0, 1)` génère une valeur flottante aléatoire dans cet intervalle.

```cpp
if (true_with_probability(0.2f)){
    image.pixel(x, y).r = random_float(0, 1);
    image.pixel(x, y).g = random_float(0, 1);
    image.pixel(x, y).b = random_float(0, 1);
}
```
**Résultat final :**

![noise.png](/output/noise.png)


### Rotation de 90° ⭐⭐

Ici, il faut **créer une nouvelle image avec de nouvelles dimensions** car quand on rotate de 90 degrés une image, **sa largeur devient sa longueur et inversement.**


Chaque pixel (x, y) de la nouvelle image est rempli avec la valeur d'un pixel de l'image d'origine.

Pour faire la rotation de 90° :
- la colonne de pixels x dans la nouvelle image correspond à ligne x de l'image d'origine.
- La ligne y dans la nouvelle image correspond à la colonne inversée de l'image d'origine `(image.width() - 1 - y)`.

**Résultat final :**

![rotating.png](/output/rotation.png)

### RGB Split ⭐⭐

Pour cet exercice, **il faut une nouvelle image et travailler sur celle-ci.** Il ne faut pas modifier l'image originale pendant que nous bouclons pour appliquer l'effet, sinon certains pixels n'utiliseront pas la bonne couleur de l'image originale, mais plutôt la couleur déjà modifiée par un pixel précédent.

```cpp
sil::Image image_split{image.width(), image.height()};
```
Chaque pixel va prendre comme couleur **le rouge d'un pixel un peu à sa droite, son propre vert, et le bleu d'un pixel un peu à sa gauche.**

**Décalage des canaux de couleur** : 
```cpp

if (x >= 30)
{
    image_split.pixel(x, y).r = image.pixel(x - 30, y).r;
}
if (x < image.width() - 31)
{
    image_split.pixel(x, y).b = image.pixel(x + 30, y).b;
}
image_split.pixel(x, y).g = image.pixel(x, y).g;

```
- Le rouge est décalé de 30 pixels vers la gauche.
- Le bleu est décalé de 30 pixels vers la droite.

A la fin, on remplace l'image par la nouvelle avec `image = image_split;`
  
**Résultat final :**

![rgb_split.png](/output/rgb_split.png)

### Mosaïque ⭐⭐

On commence par **créer les dimensions de la nouvelle image** :

```cpp
int new_width = image.width() * 5;
int new_height = image.height() * 5;
sil::Image new_image{new_width, new_height};
```
Ensuite, **on récupère les pixels d'origine :**

```cpp
int old_x = x % image.width();
int old_y = y % image.height();
```
`old_x` correspond à la position dans l'image d'origine pour la colonne actuelle de la nouvelle image. De la même manière, `old_y` correspond également à la ligne d'origine.

La **fonction % (modulo)** assure que la valeur de old_x est toujours dans la l'intervale **[0, image.width() - 1]**. Cette utilisation du modulo permet de répéter les pixels de l'image d'origine.

**Résultat final :**

![mosaique.png](/output/mosaique.png)


### Mosaïque miroir ⭐⭐⭐⭐

Cet exercice reprend le précédent mais le complexifie. En effet, il faut **inverser une image sur deux**. 

Pour appliquer la transformation miroir, il suffit de faire : 

```cpp
bool mirrorX{(x / image.width()) % 2 == 1};
bool mirrorY{(y / image.height()) % 2 == 1};
```

Ensuite, pour l'inversion des coordonnées, cela est fait grâce à des `if` de la manière suivante :
```cpp
if (mirrorX)
{
    old_x = image.width() - old_x - 1;
}
if (mirrorY)
{
    old_y = image.height() - old_y - 1;
}
```
Sans oublier la **copie du pixel** : 

```cpp
mosaique.pixel(x, y) = image.pixel(old_x, old_y);
```

Puis **remplacer l'image originale par la mosaïque** :

```cpp
image = mosaique;
```
**Résultat final :**

![mosaic_mirror.png](/output/mosaic_mirror.png)
###  Glitch ⭐⭐⭐

Pour faire cet exercice, je me suis basé sur un **rectangle de pixels et je l'ai l'interverti avec un autre rectangle de pixels**, ailleurs dans l'image. Et j'ai répété cette action. 

On définit le nombre de glitch qu'on souhaite avec `int number_glitch = 80;`.

Il y a une boucle `for` allant jusqu'à `number_glitch` permettant de créer le nombre de glitch voulu. 

Il faut ensuite générer les rectangles : 

**Rectangle 1 :**
```cpp
int rectangle1_x = random_int(0, image.width() - 1);
int rectangle1_y = random_int(0, image.height() - 1);
int rectangle_width = random_int(5, 20);
int rectangle_height = random_int(1, 10);
```
J'utilise `random_int` pour avoir des **tailles aléatoires de rectangles** à des **endroits également aléatoires.**

**Rectangle 2 :**

```cpp
int rectangle2_x = random_int(0, image.width() - 1);
int rectangle2_y = random_int(0, image.height() - 1);
```
*Ces rectangles permettront de déterminer les blocs de pixels à échanger.*

On s'assure que **les rectangles ne dépassent pas la taille de l'image avec :** 

```cpp
rectangle_width = std::min(rectangle_width, image.width() - std::max(rectangle1_x, rectangle2_x));
rectangle_height = std::min(rectangle_height, image.height() - std::max(rectangle1_y, rectangle2_y));
```
On termine avec les deux boucles for qui parcourent les pixels et **swap** les positions des deux rectangles.

```cpp
std::swap(image.pixel(rectangle1_x + x, rectangle1_y + y), image.pixel(rectangle2_x + x, rectangle2_y + y));
```

**Résultat final :**

![glitch.png](/output/glitch.png)
### Tri de pixels ⭐⭐⭐
Pour cet exercice, la boucle principale parcourt les pixels de l'image par blocs de taille 70 :

```cpp
for (int i = 0; (i + 70) < image.pixels().size(); i++)
```

Il faut aussi déterminer aléatoirement si un bloc est trié ou non. J'utilise un `if (random_int(0, 150) == 75)`

Ici, le code trie les pixels par luminosité (grâce à `std::sort`) : 

```cpp
std::sort(image.pixels().begin() + i, image.pixels().begin() + (i + 70), [](glm::vec3 const &color1, glm::vec3 const &color2)
          { return brightness(color1) > brightness(color2); });
```
Il faut également indiquer le critère de tri : 

```cpp
brightness(color1) > brightness(color2)
```
Et on passe au bloc suivant.

**Résultat final :**

![pixel_sorting.png](/output/pixel_sorting.png)
### Vortex ⭐⭐⭐⭐

On calcule la **distance par rapport au centre :**
```cpp 
glm::vec2 current_point{x, y};
glm::vec2 center_of_rotation{image.width() / 2, image.height() / 2};
```
Puis l'**angle de rotation puis sa rotation :**

```cpp
float distance = glm::distance(current_point, center_of_rotation);
------------------------------------------------------------------------------------------------
glm::vec2 rotated_point = glm::vec2{glm::rotate(glm::mat3{1.f}, angle) * glm::vec3{current_point - center_of_rotation, 0.f}} + center_of_rotation;
```
(Voir le reste du code source pour plus d'informations).

**Résultat final :**

![vortex.png](/output/vortex.png)
## Exercices avec l'image photo.jpg

Maintenant, je  vais expliquer les exercices se basant sur l'image photo.jpg.

Voici les exercices réalisés avec l'image de base suivante : 

![logo.png](/images/photo.jpg)

### Luminosité ⭐⭐
Pour cet exercice, je me suis basée sur les **fonctions puissance.** 

#### Eclaircissement
On cherche à **augmenter** tous les nombres entre 0 et 1 en gardant 0 à 0 et 1 à 1. 

On modifie donc les composantes RGB en utilisant la **racine carrée** `std::sqrt`. Elle sert à accentuer les faibles valeurs et donc **éclaircir les zones sombres.**

```cpp
image.pixel(x, y).r = std::sqrt(image.pixel(x, y).r);
image.pixel(x, y).g = std::sqrt(image.pixel(x, y).g);
image.pixel(x, y).b = std::sqrt(image.pixel(x, y).b);
```
**Résultat final :**

![light_luminosity
.png](/output/light_luminosity.png)
#### Assombrissement 
On fait le procédé inverse, c'est à dire qu'on cherche à assombrir les pixels donc diminuer tous les nombres entre 0 et 1 en gardant 0 à 0 et 1 à 1.

On modifie donc les composantes RGB en utilisant la **puissance de 2** `std::sqrt`. Elle sert à accentuer les faibles valeurs et donc **assombrir les zones claires.**

```cpp
image.pixel(x, y).r = std::pow(image.pixel(x, y).r, 2);
image.pixel(x, y).g = std::pow(image.pixel(x, y).g, 2);
image.pixel(x, y).b = std::pow(image.pixel(x, y).b, 2);
```
**Résultat final :**

![dark_luminosity.png](/output/dark_luminosity.png)

### Tramage ⭐⭐⭐(⭐)

J'ai utilisé la matrice de Bayer qui aide à faire l'effet voulu. 

```cpp
const int bayer_n = 4;
float bayerMatrix[bayer_n][bayer_n] = {
    {-0.5, 0, -0.375, 0.125},
    {0.25, -0.25, 0.375, -0.125},
    {-0.3125, 0.1875, -0.4375, 0.0625},
    {0.4375, -0.0625, 0.3125, -0.1875},
};
```

Puis on calcule la **luminosité** du pixel :
```cpp
float bright = brightness(image.pixel(x, y));
```

(Voir le code source pour le reste)

**Résultat final :**

![dithering.png](/output/dithering.png)


### Normalisation de l'histogramme ⭐⭐⭐(⭐)
Pour cet exercice, on part d'une image différente que d'habitude :

**Photo faible contraste**

![photo_faible_contraste.jpg](/images/photo_faible_contraste.jpg)



L'algorithme consiste à trouver le pixel le moins lumineux et le pixel le plus lumineux de l'image, puis à appliquer une **transformation** à chaque pixel de sorte à ce que **le pixel le plus sombre devienne un noir pur (0) et le plus lumineux devienne un blanc pur (1).**

On initialise les variables suivantes : 

```cpp
float darkest = 1.f;
float whitest = 0.f;
```
On calcule la **luminosité du pixel** avec :

```cpp
float lum = brightness(pixel);
```
Puis on **met à jour les valeurs des luminosités minimales et maximales :** 
```cpp
if (lum < darkest)
{
    darkest = lum;
}
else if (lum > whitest)
{
    whitest = lum;
}
```

Ici, la nouvelle chose du programme est la **normalisation** : 
```cpp
float normalizedLum = (lum - darkest) / (whitest - darkest);
```

 Cela permet de **transformer la luminosité du pixel pour la rendre proportionnelle entre les valeurs de darkest et whitest.**

Il faut ensuite **mettre à jour la luminosité du pixel :** 

```cpp
pixel = pixel * (normalizedLum / lum);
```

**Résultat final :**

![histogram.png](/output/histogram.png)


## Exercices à partir de rien (pas d'images de base)

### Dégradé ⭐
Pour réaliser ce dégradé, j'ai utilisé cette formule : 
```cpp
image.pixel(x, y) = glm::vec3{static_cast<float>(x) / static_cast<float>(image.width() - 1)};
```
**Résultat final :**

![disk.png](/output/gradiant.png)

### Disque ⭐⭐(⭐)
On cherche à réaliser un disque.

Je commence par créer l'image de travail 
```cpp
sil::Image image{500/*width*/, 500/*height*/};
```
Puis je continue en **initialisant les variables :**
```cpp
int h{image.width() / 2};
int k{image.height() / 2};
int r{100};
```
- **Variable h** -> centre horizontal situé au milieu de la largeur de l'image.
- **Variable k** -> centre vertical situé au milieu de la hauteur de l'image.
- **Variable r** -> rayon du disque, défini à 100 pixels. Cela détermine la taille du disque.
On va ensuite se baser sur l'équation du cercle :

$$
(x-h)²+(y-k)² = r²
$$

L'expression `pow(x - h, 2) + pow(y - k, 2)` calcule la distance au carré entre le pixel `(x, y)` et le centre du disque `(h, k)`.

Et si le pixel est à **l'intérieur du disque :**
```cpp
image.pixel(x, y).r = 1;
image.pixel(x, y).g = 1;
image.pixel(x, y).b = 1;
```
Si il est **en dehors** : 
```cpp
image.pixel(x, y).r = 0;
image.pixel(x, y).g = 0;
image.pixel(x, y).b = 0;
```
**Résultat final :**

![disk.png](/output/disk.png)

### Cercle ⭐
Pour celui là, on se base sur le code précédant et on rajoute une variable thickness. 

```cpp
int thickness{10};
```

On fait des if afin de créer le cercle : 

```cpp
if (pow(x - h, 2) + pow(y - k, 2) < pow(r - thickness, 2))
{
    image.pixel(x, y).r = 0;
    image.pixel(x, y).g = 0;
    image.pixel(x, y).b = 0;
}
else if (pow(x - h, 2) + pow(y - k, 2) < pow(r, 2))
{
    image.pixel(x, y).r = 1;
    image.pixel(x, y).g = 1;                image.pixel(x, y).b = 1;
}

else
{
    image.pixel(x, y).r = 0;
    image.pixel(x, y).g = 0;
    image.pixel(x, y).b = 0;
}
```

- **Premier if :** Cette condition vérifie si un pixel se trouve à l'intérieur de l'anneau qui constitue la bordure du cercle. Si cette condition est vraie, cela signifie que le pixel se trouve dans la bordure du cercle, et donc on le colore en noir.
- **Else if :** Si le pixel n'est pas dans la bordure, mais à l'intérieur du cercle complet, il est colorié en blanc.
- **Else :** Si le pixel est en dehors du cercle, il est colorié en noir.

**Résultat final :**

![circle.png](/output/circle.png)

### Animation ⭐⭐
Le but est de créer une animation où **le cercle blanc se déplace horizontalement à travers l'image, et l'image est sauvegardée à chaque étape.**

J'utilise une variable que j'initialise à 0 et une boucle `while` pour chaque frame.
J'utilise une autre variable qui elle permet de créer le coordonnée vertical du centre du cercle et qui permettra de le déplacer. 

**Résultat final :**

J'ai sauvegardé les images dans le répertoire **/anim** mais je n'ai aps créé l'animation sur le site de gif.

### Rosace ⭐⭐⭐
Création de la rosace composée de plusieurs cercles disposés de manière symétrique autour du centre de l'image.

Voici le code entier : 

```cpp
void rosace(sil::Image &image)
{

    int r{100};
    int thickness{5};

    for (int x{0}; x < image.width(); x++)

    {
        for (int y{0}; y < image.height(); y++)

        {

            int dx = x - image.width() / 2;
            int dy = y - image.height() / 2;
            if ((dx * dx + dy * dy <= r * r) && (dx * dx + dy * dy > (r - thickness) * (r - thickness)))
            {
                image.pixel(x, y).r = 1.0f;
                image.pixel(x, y).g = 1.0f;
                image.pixel(x, y).b = 1.0f;
            }
        }
    }
    int centreX = image.width() / 2;
    int centreY = image.height() / 2;
    float angleStep = 2 * 3.14 / 6;
    for (int i = 0; i < 6; i++)
    {
        float angle = i * angleStep;
        int offsetX = static_cast<int>(r * cos(angle));
        int offsetY = static_cast<int>(r * sin(angle));

        for (int x = 0; x < image.width(); x++)
        {
            for (int y = 0; y < image.height(); y++)
            {
                int dx = x - centreX - offsetX;
                int dy = y - centreY - offsetY;

                if ((dx * dx + dy * dy <= r * r) && (dx * dx + dy * dy > (r - thickness) * (r - thickness)))
                {
                    image.pixel(x, y).r = 1.0f;
                    image.pixel(x, y).g = 1.0f;
                    image.pixel(x, y).b = 1.0f;
                }
            }
        }
    }
}
```

Nous pouvons y retrouver le **calcul des coordonnées du centre, de la condition pour dessiner le cercle, du calcul des positions des cercles et du dessin des cercles déplacés.**


**Résultat final :**

![rosace.png](/output/rosace.png)

### Fractale de Mandelbrot

- On initialise les couleurs
- On parcourt l'ensemble des pixels de l'image
- On définit par la suite des coordonnées complexes
- On initialise la suite de Mandelbrot
- On l'itère
- On rajoute des conditions
  
```cpp
void mandelbrot_fractal(sil::Image &image)
{

    glm::vec3 black{0, 0, 0};
    glm::vec3 white{1, 1, 1};

    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

            std::complex<float> c{static_cast<float>(x) / 200 - 1.75f, static_cast<float>(y - 250) / 200}; // Définis le nombre z = 3 + 2*i
            std::complex<float> z{0, 0};

            for (int i = 0; i < 50; i++)
            {
                z = z * z + c;
                if (std::abs(z) > 2)
                {
                    image.pixel(x, y) = glm::vec3{static_cast<float>(i) / 50.f};
                    break;
                }
            }
            if (std::abs(z) < 2)
            {
                image.pixel(x, y) = white;
            }
        }
    }
}
```


**Résultat final :**

![fractale.png](/output/fractale.png)


## Quelques ratés
Durant cette semaine, certains tests n'ont pas abouti au résultat voulu mais ont donné des résultats sympathiques. En voici quelques uns. 

![fractale.png](/output/red_yellow.png)

```cpp
void black_white(sil::Image &image)
{
    for (int x{0}; x < image.width(); x++)
    {
        for (int y{0}; y < image.height(); y++)
        {

        image.pixel(x, y) += 0.21 * image.pixel(x, y).r + 0.72 * image.pixel(x, y).g + 0.07 * image.pixel(x, y).b;
        }
    }
}
```
------------------------------------------

![triangular_imac.png](/output/triangular_imac.png)

```cpp
   void luminosity(sil::Image&image){
    for (int y{0}; y < image.height(); y++)
    {
        for (int x{0}; x < image.width(); x++)
        {
            image.pixel(x, y).r = x - exp(x);
        }
    }
}
```
---

![blue_green_glitch.png](/output/blue_green_glitch.png)

```cpp
void pixel_tri(sil::Image &image)
{
auto& pixels = image.pixels();  :
for (glm::vec3& color : image.pixels())
{
    color.r = 0.f;
}
    std::sort(pixels.begin(), pixels.end(), [](glm::vec3 const& color1, glm::vec3 const& color2) {
        return color1.r < color2.r; 
    });
}
```