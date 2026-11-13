# Инструкция для ИИ-агента соавтора (turiaart)

Передай этот файл своему агенту целиком. Репозиторий: https://github.com/deriio/Infinite-TU

## Ветки — кто что трогает

| Ветка | Владелец | Правило |
|---|---|---|
| `main` | никто | зеркало апстрима n1m21n/Infinite. **Никогда не коммитить и не пушить.** |
| `my/main` | deriio | интеграционная ветка форка, из неё собираются релизы. **Напрямую не пушить.** |
| `my/*` | deriio и его агенты | **не трогать.** |
| `tu/main` | turiaart | её интеграционная ветка: сюда вливаются её задачи, отсюда deriio забирает в `my/main`. |
| `tu/<задача>` | агенты turiaart | одна ветка = одна задача, создаётся от `tu/main`. |

## Как начать задачу

```bash
git clone https://github.com/deriio/Infinite-TU.git && cd Infinite-TU   # один раз
git fetch origin
git switch -c tu/<короткое-имя> origin/tu/main    # новая ветка от свежего tu/main
```

Сабмодули (обязательно перед первой сборкой, иначе CMake: «VST3 SDK was not found»):
```bash
git submodule update --init external/vst3sdk
git -C external/vst3sdk submodule update --init base cmake pluginterfaces public.sdk
```
Без `--recursive` — он тянет гигабайты документации. Если VST3-плагины не нужны: `cmake ... -DINFINITE_ENABLE_VST3=OFF`.

## Во время работы

- Мелкие коммиты с понятными сообщениями. Изменения в коде апстрима помечать комментарием `// fork:` и строкой в `docs/fork-changes.md`.
- Не переформатировать чужой код, не переименовывать файлы без нужды — это главный источник конфликтов.
- Не трогать `scripts/fork-sync.sh`, `.github/workflows/`, `src/**/ForkIdentity.h` без согласования.
- Никаких ключей/токенов в файлах и коммитах.
- Пуш: `git push -u origin tu/<имя>`. Без `--force` (разве что в свою ветку, если она ещё ни с кем не делится).

## Держать ветку свежей

Если `tu/main` ушёл вперёд:
```bash
git fetch origin && git merge origin/tu/main     # merge, не rebase — история уже на GitHub
```
Конфликты решать, сохраняя обе стороны; если непонятно — остановиться и спросить.

## Проверка перед сдачей

1. Сборка проходит (Windows: Visual Studio 2022 + CMake, см. `docs/WINDOWS_VERIFICATION.md`; либо пуш ветки `feature/tu-<имя>` — GitHub Actions соберёт Windows-версию, ~1 час).
2. То, что поменяла, проверено руками в приложении.
3. Коротко записать в `docs/changelog.md`: что сделано, что проверено, что нет.

## Как сдать

Открыть Pull Request **из `tu/<имя>` в `tu/main`** (не в `main` и не в `my/main`!):
```bash
gh pr create --base tu/main --head tu/<имя> --title "..." --body "что сделано / как проверить"
```
turiaart (или её агент) смотрит и сливает в `tu/main`. После слияния ветку задачи можно удалить.

## Обмен между tu/main и my/main

- **Хотя бы раз в неделю** (и перед крупной задачей) подтягивать наше в своё:
  `git switch tu/main && git merge origin/my/main && git push` — конфликты решать сразу, пока они мелкие.
- Когда в `tu/main` накопилось готовое — открыть PR **`tu/main` → `my/main`**; deriio проверяет и сливает, оно попадает в релиз.
- Чем чаще обмен, тем меньше конфликтов: две ветки, которые месяц живут отдельно, сливать больно.
