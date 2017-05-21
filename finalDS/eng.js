module.exports = `Abstract
Image-to-image translation is a class of vision and graphics problems where the goal is to learn the mapping between an input image and an output image using a train- ing set of aligned image pairs. However, for many tasks, paired training data will not be available. We present an approach for learning to translate an image from a source domain X to a target domain Y in the absence of paired examples. Our goal is to learn a mapping G : X → Y such that the distribution of images from G(X) is indistin- guishable from the distribution Y using an adversarial loss. Because this mapping is highly under-constrained, we cou- ple it with an inverse mapping F : Y → X and introduce a cycle consistency loss to push F(G(X)) ≈ X (and vice versa). Qualitative results are presented on several tasks where paired training data does not exist, including col- lection style transfer, object transfiguration, season trans- fer, and photo enhancement, etc. Quantitative comparisons against several prior methods demonstrate the superiority of our approach.
1. Introduction
What did Claude Monet see as he placed his easel by the bank of the Seine near Argenteuil on a lovely spring day in 1873 (Figure 1, top-left)? A color photograph, had it been invented, may have documented a crisp blue sky and a glassy river reflecting it. Monet conveyed his impression of this same scene through wispy brush strokes and a bright palette.
What if Monet had happened upon the little harbor in Cassis on a cool summer evening (Figure 1, bottom-left)? A brief stroll through a gallery of Monet paintings makes it easy to imagine how he would have rendered the scene: perhaps in pastel shades, with abrupt dabs of paint, and a somewhat flattened dynamic range.
We can imagine all this despite never having seen a side by side example of a Monet painting next to a photo of the scene he painted. Instead we have knowledge of the set of Monet paintings and of the set of landscape photographs.
* indicates equal contribution
 1
arXiv:1703.10593v1 [cs.CV] 30 Mar 2017
 Paired Unpaired Figure 2: Paired training data (left) consists of training ex- amples {xi,yi}Ni=1, where the yi that corresponds to each xi is given [18]. We instead consider unpaired training data (right), consisting of a source set {xi}Ni=1 ∈ X and a target set {yj }Mj =1 ∈ Y , with no information provided as to which xi matches which yj .
We can reason about the stylistic differences between these two sets, and thereby imagine what a scene might look like if we were to “translate” it from one set into the other.
In this paper, we present a system that can learn to do the same: capturing special characteristics of one image col- lection and figuring out how these characteristics could be translated into the other image collection, all in the absence of any paired training examples.
This problem can be more broadly described as image- to-image translation [18], converting an image from one representation of a given scene, x, to another, y, e.g., greyscale to color, image to semantic labels, edge-map to photograph. Years of research in computer vision, image processing, and graphics have produced powerful transla- tion systems in the supervised setting, where example im- age pairs {x, y} are available, e.g., [8, 15, 18, 19, 23, 28, 40, 50, 52, 55] (Figure 2, left). However, obtaining paired training data can be difficult and expensive. For example, only a couple of datasets exist for tasks like semantic seg- mentation (e.g., [3]), and they are relatively small. Obtain- ing input-output pairs for graphics tasks like artistic styliza- tion can be even more difficult since the desired output is highly complex, typically requiring artistic authoring. For many tasks, like object transfiguration (e.g., zebra→horse, Figure 1 top-middle), the desired output is not even well- defined.
We therefore seek an algorithm that can learn to trans- late between domains without paired input-output examples (Figure 2, right). We assume there is some underlying rela- tionship between the domains – for example, that they are two different renderings of the same underlying world – and seek to learn that relationship. Although we lack supervi- sion in the form of paired examples, we can exploit super- vision at the level of sets: we are given one set of images in
fails to make progress [12].
These issues call for adding more structure to our ob-
jective. We therefore exploit the property that translation should be “cycle consistent”, in the sense that if we trans- late, e.g., a sentence from English to French, and then trans- late it back from French to English, we should arrive back at the original sentence. Mathematically, if we have a trans- latorG : X → Y andanothertranslatorF : Y → X, then G and F should be inverses of each other, and both mappings should be bijections. We apply this structural as- sumption by training both the mapping G and F simultane- ously, and adding a cycle consistency loss that encourages F (G(x)) ≈ x and G(F (y)) ≈ y. Combining this loss with adversarial losses on domains X and Y yields our full ob- jective for unpaired image-to-image translation.
We apply our method on a wide range of applications, in- cluding style transfer, object transfiguration, attribute trans- fer and photo enhancement. We also compare against pre- vious approaches that rely either on hand-defined factoriza- tions of style and content, or on shared embedding func- tions, and show that our method outperforms these base- lines. Our code is available at https://github.com/ junyanz/CycleGAN.
2. Related work
Generative Adversarial Networks (GANs) [13, 56] have achieved impressive results in image generation [4, 33], image editing [59], and representation learning [38]. Recent methods adopt the same idea for conditional image generation applications, such as text2image [35], image in- painting [32], and future prediction [31], as well as to other domains like videos [48] and 3D models [51]. The key to GANs’ success is the idea of an adversarial loss that forces the generated images to be, in principle, indistinguishable from real images. This is particularly powerful for image generation tasks, as this is exactly the objective that much of computer graphics aims to optimize. We adopt an ad-
domain X and a different set in domain Y . We may train ) a mapping G : X → Y such that the output yˆ = G(x), x ∈ X, is indistinguishable from images y ∈ Y by an ad- versary trained to classify yˆ apart from y. In theory, this ob- jective can induce an output distribution over yˆ that matches the empirical distribution pY (y) (in general, this requires that G be stochastic) [13]. The optimal G thereby trans- lates the domain X to a domain Yˆ distributed identically to Y . However, such a translation does not guarantee that the individual inputs and outputs x and y are paired up in a meaningful way – there are infinitely many mappings G that will induce the same distribution over yˆ. Moreover, in practice, we have found it difficult to optimize the adversar- ial objective in isolation: standard procedures often lead to the well-known problem of mode collapse, where all input images map to the same output image, and the optimization
cycle-consistency loss
cycle-consistency loss
  (b)
(c)
Figure 3: (a) Our model contains two mapping functions G : X → Y and F : Y → X, and associated adversarial discriminators DY and DX . DY encourages G to translate X into outputs indistinguishable from domain Y , and vice versa for DX, F, and X. To further regularize the mappings, we introduce two “cycle consistency losses” that capture the intuition that if we translate from one domain to the other and back again we should arrive where we started: (b) forward cycle-consistency loss: x → G(x) → F (G(x)) ≈ x, and (c) backward cycle-consistency loss: y → F (y) → G(F (y)) ≈ y
versarial loss to learn the mapping such that the translated image cannot be distinguished from images in the target do- main.
Image-to-Image Translation The idea of image-to- image translation goes back at least to Hertzmann et al.’s Image Analogies [15], which employs a nonparametric tex- ture model [7] from a single input-output training image pair. More recent approaches use a dataset of input-output examples to learn a parametric translation function using CNNs [28]. Our approach builds on the “pix2pix” frame- work of Isola et al. [18], which uses a conditional generative adversarial network [13] to learn a mapping from input to output images. Similar ideas have been applied to various tasks such as generating photographs from sketches [39] or from attribute and semantic layouts [20]. However, un- like these prior works, we learn the mapping without paired training examples.
Unpaired Image-to-Image Translation Several other methods also tackle the unpaired setting, where the goal is to relate two data domains, X and Y . Rosales et al. [36] propose a Bayesian framework that includes a prior based on a patch-based Markov random field computed from a source image, and a likelihood term obtained from multi- ple style images. More recently, CoupledGANs [27] and cross-modal scene networks [1] use a weight-sharing strat- egy to learn a common representation across domains. Con- current to our method, Liu et al. [26] extends this frame- work with a combination of variational autoencoders [22] and generative adversarial networks. Another line of con- current work [41, 44, 2] encourages the input and output to share certain “content” features even though they may differ in “style“. They also use adversarial networks, with addi- tional terms to enforce the output to be close to the input in a pre-defined metric space, such as class label space [2], image pixel space [41], and image feature space [44].
Unlike the above approaches, our formulation does not rely on any task-specific, pre-defined similarity function be-
tween the input and output, nor do we assume that the in- put and output have to lie in the same low-dimensional em- bedding space. This makes our method a general-purpose solution for many vision and graphics tasks. We directly compare against several prior approaches in Section 5.1.
Neural Style Transfer [10, 19, 46, 9] is another way to perform image-to-image translation, which synthesizes a novel image by combining the content of one image with the style of another image (typically a painting) by match- ing the Gram matrix statistics of pre-trained deep features. Our main focus, on the other hand, is learning the map- ping between two domains, rather than between two spe- cific images, by trying to capture correspondences between higher-level appearance structures. Therefore, our method can be applied to other tasks, such as painting→ photo, ob- ject transfiguration, etc. where single sample transfer meth- ods do not perform well.
Cycle Consistency The idea of using transitivity as a way to regularize structured data has a long history. In vi- sual tracking, enforcing simple forward-backward consis- tency has been a standard trick for decades [43]. More recently, higher-order cycle consistency has been used in structure from motion [54], 3D shape matching [17], co- segmentation [49], dense semantic alignment [57, 58], and depth estimation [11]. Of these, Zhou et al. [58] and Godard et al. [11] are most similar to our work, as they use a cycle consistency loss as a way of using transitivity to supervise CNN training. In this work, we are introducing a similar loss to push G and F to be consistent with each other.
3. Formulation
Our goal is to learn mapping functions between two do- mains X and Y given training samples {xi}Ni=1 ∈ X and {yj }Mj =1 ∈ Y . As illustrated in Figure 3 (a), our model in- cludestwomappingsG : X → Y andF : Y → X. In addition, we introduce two adversarial discriminators DX and DY , where DX aims to distinguish between images
(
(
 Input 𝑥 Generated image 𝐺(𝑥) Reconstruction F(𝐺 𝑥 )
             Figure 4: The reconstructed images F (G(x)) from various experiments. From top to bottom: photo↔Cezanne, horses↔zebras, winter→summer Yosemite, aerial maps↔maps on Google Maps.
{x} and translated images {F(y)}; in the same way, DY aims to discriminate between {y} and {G(x)}. Our objec- tive contains two terms: an adversarial loss [13] for match- ing the distribution of generated images to the data distri- bution in the target domain; and a cycle consistency loss to prevent the learned mappings G and F from contradicting each other.
3.1. Adversarial Loss
We apply adversarial losses [13] to both mapping func- tions. For the mapping function G : X → Y and its dis- criminator DY , we express the objective as:
LGAN(G, DY , X, Y ) =Ey∼pdata(y)[log DY (y)] +Ex∼pdata(x)[log(1 − DY (G(x))],
(1) where G tries to generate images G(x) that look simi-
lar to images from domain Y , while DY aims to dis- tinguish between translated samples G(x) and real sam- ples y. G tries to minimize this objective against an adversarial D that tries to maximize it, i.e. G∗ = argminGmaxDY LGAN(G,DY,X,Y). We introduce a similar adversarial loss for the mapping function F : Y → X and its discriminator DX as well: i.e. F∗ = argminF maxDX LGAN(F,DX,Y,X).
3.2. Cycle Consistency Loss
Adversarial training can, in theory, learn mappings G and F that produce outputs identically distributed as target domains Y and X respectively (strictly speaking, this re- quires G and F to be stochastic functions) [12]. However, with large enough capacity, a network can map the same set of input images to any random permutation of images in the target domain, where any of the learned mappings can induce an output distribution that matches the target distri- bution. Thus, an adversarial loss alone cannot guarantee that the learned function can map an individual input xi to a desired output yi. To further reduce the space of possi- ble mapping functions, we argue that the learned mapping functions should be cycle-consistent: as shown in Figure 3 (b), for each image x from domain X, the image translation cycle should be able to bring x back to the original image, i.e. x → G(x) → F (G(x)) ≈ x. We call this forward cy- cle consistency. Similarly, as illustrated in Figure 3 (c), for each image y from domain Y , G and F should also satisfy backward cycle consistency: y → F (y) → G(F (y)) ≈ y. We can incentivize this behavior using a cycle consistency loss:
Lcyc (G, F ) =Ex∼pdata (x) [∥F (G(x)) − x∥1 ] +Ey∼pdata(y)[∥G(F(y)) − y∥1]. (2)
In preliminary experiments, we also tried replacing the L1 norm in this loss with an adversarial loss between F (G(x)) and x, and between G(F(y)) and y, but did not observe improved performance.
The behavior induced by the cycle consistency loss can be observed in Figure 4: the reconstructed images F (G(x)) end up matching closely to the input images x.
3.3. Full Objective
Our full objective is:
L(G, F, DX , DY ) =LGAN(G, DY , X, Y ) +LGAN(F,DX,Y,X)
+λLcyc(G,F), (3) where λ controls the relative importance of the two objec-
tives. We aim to solve:
Notice that our model can be viewed as training two “au- toencoders” [16]: we learn one autoencoder F ◦ G : X → X jointly with another G ◦ F : Y → Y . However, these au- toencoders each have special internal structure: they map an image to itself via an intermediate representation that is a translation of the image into another domain. Such a
∗∗
G ,F = argmin max L(G,F,DX,DY ). (4) F,G Dx,DY
setup can also be seen as a special case of “adversarial au- toencoders” [29], which use an adversarial loss to train the bottleneck layer of an autoencoder to match an arbitrary tar- get distribution. In our case, the target distribution for the X → X autoencoder is that of domain Y .
In Section 5.1.4, we compare our full method against the adversarial loss LGAN alone and the cycle consistency loss alone Lcyc, and empirically show that both objectives play critical roles in arriving at high-quality results. We also evaluate our method with either only forward cycle loss or only backward cycle loss, and show that a single cycle is not be sufficient to regularize the training for this under- constrained problem.
see more datasets and training details in the appendix (Sec- tion 7).
5. Results
We first compare our approach against recent methods for unpaired image-to-image translation on paired datasets where ground truth input-output pairs are available for eval- uation. We then study the importance of both the adversar- ial loss and the cycle consistency loss, and compare our full method against several variants. Finally, we demonstrate the generality of our algorithm on a wide range of applica- tions where paired data does not exist. For brevity, we refer to our method as CycleGAN.
5.1. Quantitative Evaluation
Using the same evaluation datasets and metrics as “pix2pix” [18], we quantitatively test our method on the tasks of semantic labels↔photo on the Cityscapes dataset[3], and map↔aerial photo on data scraped from Google Maps.
5.1.1 Metrics
On the maps↔photos task, we run “real vs fake” perceptual studies on Amazon Mechani- cal Turk (AMT) to assess the realism of our outputs. We follow the maps↔photos perceptual study protocol from [18], except we only gather data from 25 participants per algorithm we tested. Participants were shown a sequence of pairs of images, one a real photo or map and one fake (gen- erated by our algorithm or a baseline), and asked to click on the image they thought was real. The first 10 trials of each session were practice and feedback was given as to whether the participant’s response was correct or incorrect. The remaining 40 trials were used to assess the rate at which each algorithm fooled participants. Each session only tested a single algorithm, and participants were only allowed to complete a single session. Note that the numbers we re- port here are not directly comparable to those in [18] as our ground truth images were processed slightly differently and the participant pool we tested may be differently dis- tributed from those tested in [18] (due to running the exper- iment at a different date and time). Therefore, our numbers should only be used to compare our current method against the baselines (which were run under identical conditions),
rather than against [18].
FCN score Although perceptual studies may be the gold standard for assessing graphical realism, we also seek an automatic quantitative measure that does not require human experiments. For this we adopt the “FCN score” from [18], and use it to evaluate the Cityscapes labels→photo task.
4. Implementation
Network Architecture
We adapt the architecture for our
generative networks from Johnson et al. [19] who have
shown impressive results for neural style transfer and super-
resolution. This network contains two stride-2 convolu-
tions, several residual blocks [14], and two fractionally-
strided convolutions with stride 1 . We use 6 blocks for 2
128 × 128 images, and 9 blocks for 256 × 256 and higher- resolution training images. Similar to Johnson et al. [19], we use instance normalization [47]. For the discriminator networks we use 70×70 PatchGANs [18, 25, 24], which try to classify whether 70 × 70 overlapping image patches are real or fake. Such a patch-level discriminator architecture has fewer parameters than a full-image discriminator, and can be applied to arbitrarily-sized images in a fully convo- lutional fashion.
Training details We apply two techniques from prior works to stabilize our model training procedure. First, for LGAN (Equation 1), we replace the negative log likelihood objective by a least square loss [30]. This loss performs more stably during training and generates higher quality re- sults. Equation 1 then becomes:
AMT perceptual studies
 LLSGAN(G, DY , X, Y ) =Ey∼pdata(y)[(DY (y) − 1)2] +Ex∼pdata (x) [DY (G(x))2 ],
(5)
Second, to reduce model oscillation [12], we follow Shrivastava et al’s strategy [41] and update discriminators DX and DY using a history of generated images rather than the ones produced by the latest generative networks. We keep an image buffer that stores the 50 previously gener- ated images.
For all the experiments, we set λ = 10 in Equation 3. We use the Adam solver [21] with a batch size of 1. All net- works were trained from scratch, and trained with learning rate of 0.0002 for the first 100 epochs and a linearly decay- ing rate that goes to zero over the next 100 epochs. Please
Input BiGAN CoGAN CycleGAN pix2pix Ground truth
                     Figure 5: Different methods for mapping labels↔photos trained on cityscapes. From left to right: input, BiGAN [5, 6], CoupledGAN [27], CycleGAN (ours), pix2pix [18] trained on paired data, and ground truth.
Input BiGAN CoGAN CycleGAN pix2pix Ground truth
                           Figure 6: Different methods for mapping aerial photos↔maps on Google Maps. From left to right: input, BiGAN [5, 6], CoupledGAN [27], CycleGAN (ours), pix2pix [18] trained on paired data, and ground truth.
The FCN metric evaluates how interpretable the generated photos are according to an off-the-shelf semantic segmen- tation algorithm (the fully-convolutional network, FCN, from [28]). The FCN predicts a label map for a generated photo. This label map can then be compared against the input ground truth labels using standard semantic segmen- tation metrics described below. The intuition is that if we generate a photo from a label map of “car on road”, then we have succeeded if the FCN applied to the generated photo detects “car on road”.
5.1.2 Baselines
CoGAN [27] This method learns one GAN generator for domain X and one for domain Y . The two generators share weights on their first few layers, which encourages them to learn a shared latent representation, with the subsequent unshared layers rendering the representation into the spe- cific styles of X and Y . Translation from X to Y can be achieved by finding a latent representation that generates image X and then instead rendering this latent representa- tion into style Y .
Pixel loss + GAN [41] Like our method, Shrivastava et al.[41] uses an adversarial loss to train a translation from X to Y . Whereas we regularize the mapping with a cycle- consistency loss, Shrivastava et al.[41] regularizes via the term ∥X − Yˆ ∥1 , which encourages the translation to be near an identity mapping.
Feature loss + GAN We also test a variant of [41] where the L1 loss is computed over deep image features (VGG-16 relu4 2 [42]), rather than over RGB pixel values. Com- puting distances in deep feature space, like this, is also sometimes referred to as using a “perceptual loss” [19].
BiGAN [6, 5] Unconditional GANs [13] learn a generator G : Z → X, that maps random noise Z to images X. The BiGAN [6] and ALI [5] frameworks propose to also learn the inverse mapping function F : X → Z, which projects a generated image x back to a low-dimensional latent code z. Though originally designed for mapping a latent vector z to an image x, we implemented the same objective for mapping a source image x to a target image y.
 Semantic segmentation metrics
To evaluate the perfor- mance of photo→labels, we use the standard metrics from the Cityscapes benchmark, including per-pixel accuracy,Religion in Medieval England
We learned about the Religion in Medieval(410-1066 c.e.)British,so I
between
1.Rise of Christianity
collected and read some relevant information after class. And I interested in the
history of religion in Medieval England(They are have same historical process
religion in Medieval British and in Medieval England I guess).
There would be divide into three parts.
Christianity had been the official imperial religion of the Roman Empire,
and the first churches were built in England in the second half of the 4th
century, overseen by a hierarchy of bishops and priests. The collapse of the
Roman system in the late 5th century, however, brought about the end of
formal Christian religion in the east of England, and the new Germanic
immigrants arrived with their own polytheistic gods, including Woden , Thunor
and Tiw , still reflected in various English place names. Despite the
resurgence of paganism in England, Christian communities still survived in
more western areas such as Gloucestershire and Somerset .
The movement towards Christianity began again in the late 6th and 7th
centuries, helped by the conversion of the Franks in Northern France, who
carried considerable influence in England. Pope Gregory I sent a team of
missionaries to convert King Æthelberht of Kent and his household, starting
the process of converting Kent. Augustine became the first Archbishop of
Canterbury and started to build new churches across the South-East, reusing
existing pagan shrines.
Oswald and Oswiu , kings of Northumbria, were converted in the 630s
and 640s, and the wave of change carried on through the middle of the 7th
century across the kingdoms of Mercia, the South Saxons and the Isle of
Wight . The process was largely complete by the end of the 7th century, but
left a confusing and disparate array of local practices and religious
ceremonies. This new Christianity reflected the existing military culture of the
Anglo-Saxons: as kings began to convert in the 6th and 7th centuries,
conversion began to be used as a justification for war against the remaining
pagan kingdoms, for example, while Christian saints were imbued with martial
properties.
The Viking invasions of the 8th and 9th centuries reintroduced paganism
to North-East England, leading in turn to another wave of conversion. The
Norse settlers in England were converted relatively quickly, assimilating their
beliefs into Christianity in the decades following the occupation of York, which
the Archbishop had survived. The process was largely complete by the early
10th century and enabled England's leading Churchmen to negotiate with the
 warlords. As the Norse in mainland Scandinavia started to convert , many
 mainland rulers recruited missionaries from England to assist in the process.
 2.Religious institutions
 With the conversion of much of England in the 6th and 7th centuries,
 there was an explosion of local church building. English monasteries formed
 the main basis for the church, however, and were often sponsored by local
 rulers, taking various forms, including mixed communities headed by
 abbesses , bishop-led communities of monks , and others formed around
 married priests and their families. Cathedrals were constructed, staffed either
 with secular canons in the European tradition or, uniquely to England,
 chapters of monks. These institutions were badly affected in the 9th century
 by Viking raids and predatory annexations by the nobility. By the start of the
 10th century, monastic lands, financial resources and the quality of
 monasteries' religious work had been much diminished.
 Reforms followed under the kings of Wessex who promoted the
 Benedictine rule then popular on the Continent. A reformed network of around
 40 monastic institutions across the south and east of England, under the
 protection of the king, helped re-establish royal control over the reconquered
 Danelaw.
 The 1066 Norman conquest brought a new set of Norman and French
 churchmen to power; some adopted and embraced aspects of the former
 Anglo-Saxon religious system, while others introduced practices from
 Normandy. Extensive English lands were granted to monasteries in
 Normandy, allowing them to create daughter priories and monastic cells
 across the kingdom. The monasteries were brought firmly into the web of
 feudal relations, with their holding of land linked to the provision of military
 support to the crown. The Normans adopted the Anglo-Saxon model of
 monastic cathedral communities, and within seventy years the majority of
 English cathedrals were controlled by monks; every English cathedral,
 however, was rebuilt to some extent by the new rulers. England's bishops
 remained powerful temporal figures, and in the early 12th-century raised
 armies against Scottish invaders and built up extensive holdings of castles
 across the country.
 3.Church, State and Heresy
 The Church had a close relationship with the English state throughout
 the Middle Ages. The bishops and major monastic leaders played an
 important part in national government, having key roles on the king's council.
Bishops often oversaw towns and cities, managing local taxation and
government . This frequently became untenable with the Viking incursions of
new accommodations with the local ealdormen , exchanging some authority
and revenue for assistance in defence. The early English church was racked
with disagreement on doctrine , which was addressed by the Synod of Whitby
in 664; some issues were resolved, but arguments between the archbishops
of Canterbury and York as to which had primacy across Britain began shortly
afterwards and continued throughout most of the medieval period.
William the Conqueror acquired the support of the Church for the
invasion of England by promising ecclesiastical reform. William promoted
celibacy amongst the clergy and gave ecclesiastical courts more power, but
also reduced the Church's direct links to Rome and made it more accountable
to the king. Tensions arose between these practices and the reforming
movement of Pope Gregory VII , which advocated greater autonomy from
royal authority for the clergy, condemned the practice of simony and promoted
greater influence for the papacy in church matters. Despite the bishops
continuing to play a major part in royal government, tensions emerged
between the kings of England and key leaders within the English Church.
Kings and archbishops clashed over rights of appointment and religious
policy, and successive archbishops including Anselm , Theobald of Bec ,
Thomas Becket and Stephen Langton were variously forced into exile,
arrested by royal knights or even killed. By the early 13th century, however,
the church had largely won its argument for independence, answering almost
entirely to Rome.Sub-Roman Britain
After the class,I find some online information about the acient history of British,and learn a lot with Wikipedia. I read some articles included in the entry named Sub- Roman Britain.And I will chose some to write down.
Meaning of terms
The period of sub-Roman Britain traditionally covers the history of the area which
subsequently became England from the end of Roman imperial rule in 410 to the
arrival of Saint Augustine in 597. The date taken for the end of this period is arbitrary
in that the sub-Roman culture continued in the West of England (see Cornwall and
Cumbria) and in Wales. This period has attracted a great deal of academic and
popular debate, in part because of the scarcity of the written source material. The
term "post-Roman Britain" is also used for the period, mainly in non-archaeological
contexts; "sub-Roman" and "post-Roman" are both terms that apply to the old
Roman province of Britannia , ie Britain south of the Forth – Clyde line. The period
may also be considered as part of the early Middle Ages , if continuity with the
following periods is stressed. Popular (and some academic) works use a range of
more dramatic names for the period: the Dark Ages , the Brythonic Age, the Age of
Tyrants, or the Age of Arthur .
Breakdown of Roman society
At the start of the 5th century, Britannia was part of the Western Roman Empire
under Honorius .
From the middle of the 5th century the Germanic raiders began to settle in the
eastern river valleys.
In the late 6th century there was another period of Saxon expansion, starting with the
capture of Searoburh in 552 by the dynasty that later ruled Wessex , and including
entry into the Cotswolds area after the Battle of Deorham , though the accuracy of
the entries in the Anglo-Saxon Chronicle for this period has been questioned. This
activity seems to have separated the Britons of the South West England (known later
as the West Welsh) from those of Wales. (Just after the period being discussed, the
Battle of Chester seems to have separated the latter from those of the north of
England.
Kingdoms
Various British kingdoms existed at some point in the period. Some changed their
names and some were absorbed by others. Not all of their names, especially in the
southeast, are known, nor are the details of their political development; some
authority structures left from the Roman period may have continued in charge of
some areas for some time. At times some of the kingdoms were united by a ruler who
was an overlord, while wars occurred between others. During the period the
boundaries are likely to have changed.
Religion
Officially the Roman Empire was Christian at the start of the 5th century, but there is
evidence of rural pagan temples being refurbished at the start of this period in
western England. However, most temples seem to have been replaced eventually by
Christian churches on the same site or nearby. "Celtic" churches or monasteries
seem to have flourished during this period in the British areas, such as that at
Glastonbury , but the "Saxons" were pagan. This reinforced a great antipathy
between the peoples. Many Roman cemeteries continued into much later times, such
as that at Cannington, Somerset . In the east there was a gradual transition among
the pagan Saxons from cremation to inhumation . Although the arrival of St Augustine
is traditionally seen as the significant Christianising event for the Saxons, a bishop
had already arrived in Kent with the king's Merovingian wife. Other Saxons remained
pagan after this time.
In 429, a British Deacon Palladius had requested support from the Pope in Rome to
combat Pelagianism .
In the north, Whithorn is said to be the earliest church in Scotland, being founded in
the 5th century by St Ninian .
End of Roman Britain
Various dates have been proposed to mark the end of Roman Britain, including the
end of Roman currency coinage importation in 402, Constantine III's rebellion in 407,
the rebellion mentioned by Zosimus in 409, and the Rescript of Honorius in 410.[43]
Unlike modern decolonisation, the dating of the end of Roman Britain is complex, and
the exact process is unknown.
There is some controversy as to why Roman rule ended in Britain. The view first
advocated by Wolfgang Mommsen was that Rome left Britain. This argument was
substantiated over time, most recently by AS Esmonde-Cleary.     According to this
argument, internal turmoil in the Roman Empire and the need to withdraw troops to
fight off barbarian armies led Rome to abandon Britain. However, Michael Jones has
advanced an alternative thesis that argues that Rome did not leave Britain, but that
Britain left Rome. He highlights the numerous usurpers who came from Britain in the
late 4th and early 5th centuries, and points out that the supply of coinage to Britain
had dried up by the early 5th century, so that administrators and troops were not
getting paid. All of this, he argues, led the British people to rebel against Rome. Both
of these arguments are open to criticism, and the question is still open. It was a
violent period, and there was probably widespread tension, alluded to in all the
written sources. This may have led to the deaths of many Britons. There are also
references to plagues. Laycock ( Britannia the Failed State , 2008) suggests tribal
conflict, possibly even starting before 410, may have sliced up much of Britain and
helped destroy the economy. The evidence from land use suggests a decline in
production, which might be a sign of population decline.`