#include "core/rules/RegrasAtaque.hpp"

double RegrasAtaque::calcularDano(const Personagem& personagem, const Ataque& ataque) {

    switch(ataque.tipo) {
        case TipoAtaque::Simples:
            return calcularDanoSimples(personagem, ataque);
        
        case TipoAtaque::Rapido:
            return calcularDanoRapido(personagem, ataque);
        
        case TipoAtaque::Forte:
            return calcularDanoForte(personagem, ataque);
    }
}

double RegrasAtaque::calcularDanoSimples(const Personagem& personagem, const Ataque& ataque) {
    Dados dados;
    return dados.rolar(1, 8);
}

double RegrasAtaque::calcularDanoRapido(const Personagem& personagem, const Ataque& ataque) {
    Dados dados;
    TipoClasse tipo = personagem.getClasse().getTipo();
    
    switch(tipo) {
        case TipoClasse::Arqueiro:
            return 2*(dados.rolar(1, 4) 
            + Regras::calcularCoeficiente(personagem.getAtaque()));
            
        case TipoClasse::Guerreiro:
            return 2*(dados.rolar(1, 4) 
            + Regras::calcularCoeficiente(personagem.getAtaque()));

        case TipoClasse::Mago:
            return dados.rolar(1, 6) 
            + Regras::calcularCoeficiente(personagem.getAtaque());

        case TipoClasse::Tanque:
            return dados.rolar(1, 6) 
            + Regras::calcularCoeficiente(personagem.getDefesa());
    }

    throw std::runtime_error("Tipo de ataque inválido");
}

double RegrasAtaque::calcularDanoForte(const Personagem& personagem, const Ataque& ataque) {
    Dados dados;
    TipoClasse tipo = personagem.getClasse().getTipo();
    IdAtaque idAtaque =  ataque.id;
    switch(tipo) {
        case TipoClasse::Arqueiro:
            if(idAtaque == IdAtaque::FlechaExplosiva)
                return dados.rolar(2, 8) 
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::TiroCerteiro)
                return dados.rolar(2, 10)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::Saraivada)
                return dados.rolar(5, 4)
                + Regras::calcularCoeficiente(personagem.getAtaque());
            if(idAtaque == IdAtaque::TiroFinal)
                return personagem.getNivel() * dados.d6() 
                + Regras::calcularCoeficiente(personagem.getAgilidade());

        case TipoClasse::Guerreiro:
            if(idAtaque == IdAtaque::FuriaBerserker)
                return dados.rolar(3, 6)
                + Regras::calcularCoeficiente(personagem.getAtaque());
            
            if(idAtaque == IdAtaque::GolpeDevastador) 
                return dados.rolar(2, 10)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::Perfuracao)
                return dados.rolar(2, 8)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::GolpeDoAbismo) {
                return personagem.getNivel() * dados.d10() 
                + Regras::calcularCoeficiente(personagem.getAtaque());
            }

        case TipoClasse::Mago:
            if(idAtaque == IdAtaque::BolaDeFogo)
                return dados.rolar(4,6)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::Raio)
                return dados.rolar(2, 10)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::DrenoDaMagia)
                return dados.rolar(1, 8)
                + Regras::calcularCoeficiente(personagem.getAtaque());

            if(idAtaque == IdAtaque::VorticeArcano)
                return personagem.getNivel() * dados.rolar(1, 6)
                + Regras::calcularCoeficiente(personagem.getAtaque());
            
        case TipoClasse::Tanque:
            if(idAtaque == IdAtaque::PancadaDeEscudo)
                return dados.rolar(1, 10)
                + Regras::calcularCoeficiente(personagem.getDefesa());

            if(idAtaque == IdAtaque::Terremoto)
                return dados.rolar(2, 6)
                + Regras::calcularCoeficiente(personagem.getDefesa());
            
            if(idAtaque == IdAtaque::BarreiraDeEspinhos)
                return dados.rolar(1, 8)
                + Regras::calcularCoeficiente(personagem.getDefesa());

            if(idAtaque == IdAtaque::Martirio)
                return personagem.getNivel() * dados.rolar(1, 8)
                + Regras::calcularCoeficiente(personagem.getDefesa());            
    }
    throw std::runtime_error("Tipo de ataque inválido");
}

