#include "database/BancoClassePersonagem.hpp"

void BancoClassePersonagem::defineClasse(TipoClasse tipo, ClassePersonagem& classe) {
    switch(tipo) {

        case TipoClasse::Arqueiro:
            classe.setDescricao("Velocidade e precisão, ataques múltiplos");
            classe.setArma("Arco");
            break;

        case TipoClasse::Guerreiro:
            classe.setDescricao("Alto dano, resistente, combate direto");
            classe.setArma("Espada");
            break;

        case TipoClasse::Mago:
            classe.setDescricao("Dano mágico elevado, baixa defesa");
            classe.setArma("Magia");
            break;

        case TipoClasse::Tanque:
            classe.setDescricao("Máxima resistência, dano baseado em Defesa");
            classe.setArma("Escudo");
            break;
    }
}

std::array<Ataque,3> BancoClassePersonagem::defineAtaques(TipoClasse tipo) {
    std::array<Ataque,3> ataques;
    switch(tipo) {

        case TipoClasse::Arqueiro:
            ataques[0] = {
                IdAtaque::Flecha,
                "Flecha",
                "Fraco porém não gasta mana.",
                TipoAtaque::Simples,
                0,
            };

            ataques[1] = {
                IdAtaque::TiroRapido,
                "Tiro Rápido",
                "Saca e solta duas flechas em sequência.",
                TipoAtaque::Rapido,
                10,
            };

            ataques[2] = 
            BancoClassePersonagem::getAtaquesFortesPossiveis(TipoClasse::Arqueiro)[0];
        break;

        case TipoClasse::Guerreiro:
            ataques[0] = {
                IdAtaque::Espada,
                "Espada",
                "Fraco porém não gasta mana.",
                TipoAtaque::Simples,
                0,
            };

            ataques[1] = {
                IdAtaque::GolpeRelampago,
                "Golpe Relâmpago",
                "Uma sequência veloz espada-cotovelo.",
                TipoAtaque::Rapido,
                15,
            };

            ataques[2] = 
            BancoClassePersonagem::getAtaquesFortesPossiveis(TipoClasse::Guerreiro)[0];
        break;

        case TipoClasse::Mago:
            ataques[0] = {
                IdAtaque::Truque,
                "Truque",
                "Fraco porém não gasta mana.",
                TipoAtaque::Simples,
                0,
            };

            ataques[1] = {
                IdAtaque::ProjetilArcano,
                "Projétil Arcano",
                "Um feitiço simples e certeiro que não precisa de foco.",
                TipoAtaque::Rapido,
                15,
            };
    
            ataques[2] = 
            BancoClassePersonagem::getAtaquesFortesPossiveis(TipoClasse::Mago)[0];
        break;

        case TipoClasse::Tanque:
            ataques[0] = {
                IdAtaque::Escudo,
                "Escudo",
                "Fraco porém não gasta mana.",
                TipoAtaque::Simples,
                0,
            };

            ataques[1] = {
                IdAtaque::Investida,
                "Investida",
                "Carregar com o escudo na frente, empurrando o inimigo.",
                TipoAtaque::Rapido,
                15,
            };

            ataques[2] = 
            BancoClassePersonagem::getAtaquesFortesPossiveis(TipoClasse::Tanque)[0];
        break;
    }
    return ataques;
}

std::array<Ataque, 4> BancoClassePersonagem::getAtaquesFortesPossiveis(TipoClasse tipo) {
    std::array<Ataque, 4> ataquesFortes;
    switch(tipo) {

        case TipoClasse::Arqueiro:
            ataquesFortes[0] = {
                IdAtaque::FlechaExplosiva,
                "Flecha Explosiva",
                "A flecha detona ao impactar, espalhando fogo nos pés do inimigo.",
                TipoAtaque::Forte,
                30,
            };

            ataquesFortes[1] = {
                IdAtaque::TiroCerteiro,
                "Tiro Certeiro",
                "Um disparo calculado que não pode errar.",
                TipoAtaque::Forte,
                35,
            };
            
            ataquesFortes[2] = {
                IdAtaque::Saraivada,
                "Saraivada",
                "Uma chuva de flechas de alta variância.",
                TipoAtaque::Forte,
                40,
            };

            ataquesFortes[3] = {
                IdAtaque::TiroFinal,
                "Tiro Final",
                "Uma única flecha disparada com precisão absoluta.",
                TipoAtaque::Forte,
                40,
            };
        break;
          
        case TipoClasse::Guerreiro:
            ataquesFortes[0] = {
                IdAtaque::FuriaBerserker,
                "Fúria Berserker",
                "O guerreiro entra em estado de fúria total.",
                TipoAtaque::Forte,
                30,
            };
            
            ataquesFortes[1] = {
                IdAtaque::GolpeDevastador,
                "Golpe Devastador",
                "Um impacto pesado que compromete a armadura do inimigo.",
                TipoAtaque::Forte,
                25,
            };

            ataquesFortes[2] = {
                IdAtaque::Perfuracao,
                "Perfuração",
                "Um golpe preciso que atravessa toda armadura.",
                TipoAtaque::Forte,
                25,
            };

            ataquesFortes[3] = {
                IdAtaque::GolpeDoAbismo,
                "Golpe do Abismo",
                "O guerreiro abandona qualquer postura defensiva e desfere tudo de uma vez.",
                TipoAtaque::Forte,
                45,
            };
        break;

            case TipoClasse::Mago:
            ataquesFortes[0] = {
                IdAtaque::BolaDeFogo,
                "Bola de Fogo",
                "Uma explosão mágica que afeta toda a área.",
                TipoAtaque::Forte,
                40,
            };

            ataquesFortes[1] = {
                IdAtaque::Raio,
                "Raio",
                "Um raio elétrico concentrado.",
                TipoAtaque::Forte,
                35,
            };

            ataquesFortes[2] = {
                IdAtaque::DrenoDaMagia,
                "Dreno da Magia",
                "O feitiço mais econômico do Mago.",
                TipoAtaque::Forte,
                20,
            };

            ataquesFortes[3] = {
                IdAtaque::VorticeArcano,
                "Vórtice Arcano",
                "Colapso de energia mágica diretamente no inimigo, contorna qualquer barreira física.",
                TipoAtaque::Forte,
                50,
            };
        break;

        case TipoClasse::Tanque:
            ataquesFortes[0] = {
                IdAtaque::PancadaDeEscudo,
                "Pancada de Escudo",
                "O escudo é usado como arma de impacto.",
                TipoAtaque::Forte,
                25,
            };

            ataquesFortes[1] = {
                IdAtaque::Terremoto,
                "Terremeto",
                "Um golpe pesado no chão que desequilibra o inimigo e fractura sua armadura.",
                TipoAtaque::Forte,
                25,
            };

            ataquesFortes[2] = {
                IdAtaque::BarreiraDeEspinhos,
                "Barreira de Espinhos",
                "O Tanque assume postura totalmente reativa.",
                TipoAtaque::Forte,
                30,
            };

            ataquesFortes[3] = {
                IdAtaque::Martirio,
                "Martírio",
                "O Tanque abaixa o escudo e absorve o próximo impacto, usando o golpe para se impulsionar.",
                TipoAtaque::Forte,
                35,
            };
        break;
    }
    return ataquesFortes;
};