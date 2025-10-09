# 📋 Sistema de Checklist Inteligente com IoT – TCC Senai

Projeto desenvolvido como parte do Trabalho de Conclusão de Curso do Técnico em Eletroeletrônica no SENAI, com foco em segurança operacional, manutenção preditiva e uso de tecnologias IoT para automação industrial.

---

## 👥 Equipe

- **Asaph Ingles Fonseca**  
- **Diogo Alves Ferreira**  
- **Eduardo Silvestre Padilha**  
- **Gustavo Ferreira Farias**  
- **Ubiratan Luzia de Loureiro Junior**  

**Orientador:** Prof. Flávio Eduardo de Moraes  
**Apoio Técnico:**  
- Prof. George Henrique Sato Wurthmann (Programação das placas)  
- Prof. Ismael (Integração com Google Sheets)

---

## 📌 Sobre o Projeto

Este projeto propõe a implementação de um **sistema de checklist digital integrado a dispositivos IoT**, com o objetivo de aumentar a segurança na operação de máquinas industriais, reduzir riscos de acidentes e otimizar os processos de manutenção preventiva.

A ideia central é utilizar microcontroladores conectados à internet para registrar e controlar a liberação de máquinas com base em um formulário de segurança (checklist), conforme exigido pela **Norma Regulamentadora NR-12**.

---

## 🚨 Problema de Pesquisa

Com a implementação da NR-12 em máquinas como tornos, é obrigatório o preenchimento de um **checklist de liberação** antes de cada turno de trabalho. Esses dados devem ser registrados e armazenados para compor um histórico de segurança e manutenção.

---

## 🎯 Objetivos

- Desenvolver um sistema com base em **IoT** para o preenchimento digital do checklist de liberação de máquina.
- Integrar **indicação visual via sinaleiro**, sinalizando a liberação ou bloqueio da máquina.
- Implementar controle de **horímetro da máquina** para realizar **manutenção preventiva**.
- Criar um sistema **flexível**, que possa ser adaptado para diferentes máquinas ou setores industriais.

---

## 💡 Justificativa

- Atender aos requisitos legais da **NR-12**, garantindo a segurança operacional.
- Reduzir paradas não planejadas e acidentes, otimizando a produção.
- Implementar um sistema de **baixo custo**, simples de operar e com grande aplicabilidade em pequenas e médias indústrias.

---

## 🔧 Tecnologias Utilizadas

| Componente         | Finalidade |
|--------------------|------------|
| **ESP32**          | Microcontrolador principal com Wi-Fi e Bluetooth integrados. Usado para processar o checklist e se conectar à internet. |
| **Arduino Nano**   | Utilizado para comunicação local com o painel de controle do torno, via Bluetooth. |
| **Google Sheets API** | Armazenamento em nuvem dos dados dos checklists e controle de histórico. |
| **Sinaleiros (LEDs)** | Indicação visual de liberação ou bloqueio da máquina. |
| **Horímetro Digital** | Registro de tempo de operação da máquina para controle de manutenção. |

---

## 🧠 Conceitos Aplicados

- **IoT (Internet das Coisas)**
- **Automação Industrial**
- **Manutenção Preditiva**
- **Segurança do Trabalho (NR-12)**
- **Comunicação Serial e Bluetooth**
- **APIs para integração com a nuvem**

---


---

## ✅ Conclusões

O sistema proposto mostrou-se eficaz em aumentar a segurança e controle sobre a operação de máquinas industriais, trazendo benefícios como:
- Redução de falhas operacionais
- Maior confiabilidade nos processos
- Facilidade de auditoria e rastreabilidade
- Baixo custo e alta replicabilidade

---

## 📬 Contato

Se tiver interesse em saber mais sobre o projeto ou quiser colaborar, entre em contato pelo LinkedIn ou GitHub.

---

> 🔧 Repositório criado com fins acadêmicos e demonstrativos. Pode ser adaptado e expandido para aplicações reais.
